
%{

#include "storage/common/list.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _SubqueryChain{
	struct Subquery *subquery;
	list_head list;
} SubqueryChain;

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  size_t order_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  list_head subquery_list;
  Order orders[MAX_NUM];
  OrderType order_type;
	char id[MAX_NUM];
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  list_init(&context->subquery_list);
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->order_length = 0;
  context->ssql->sstr.insertion.value_num = 0;
  context->ssql->sstr.errors = str;
  printf("parse sql failed. error=%s\n", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)

#define list2subquery_chain(ptr) (container_of(SubqueryChain, list, ptr))
#define subquery_chain_empty(context) (list_empty(&context->subquery_list))
#define current_subquery_chain(context) (subquery_chain_empty(context) ? NULL : list2subquery_chain(context->subquery_list.next))
#define current_subquery(context) (current_subquery_chain(context)->subquery)

void push_subquery(ParserContext *context);
struct Subquery *pop_subquery(ParserContext *context);

void push_subquery(ParserContext *context) {
	struct Subquery *subquery = (struct Subquery *)malloc(sizeof(struct Subquery));
	SubqueryChain *chain = (SubqueryChain *)malloc(sizeof(SubqueryChain));
	memset(subquery, 0, sizeof(struct Subquery));
	memset(chain, 0, sizeof(SubqueryChain));
	chain->subquery = subquery;
	list_add(&context->subquery_list, &chain->list);
}

struct Subquery *pop_subquery(ParserContext *context) {
	SubqueryChain *chain = current_subquery_chain(context);
	if (chain == NULL) {
		return NULL;
	}
	struct Subquery *ret = chain->subquery;
	list_delete(&chain->list);
	free(chain);
	return ret;
}
%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        NULL_T
        NULLABLE_T
        TABLE
        TABLES
        INDEX
        SELECT
        MAX
        MIN
        COUNT
        AVG
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        TEXT_T
        DATE_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        IN
        AND
        GROUP
        SET
        INNER
        JOIN
        ON
        IS
        LOAD
        DATA
        INFILE
        UNIQUE
	ASC
	ORDER
	BY
        EQ
        LT
        GT
        LE
        GE
        NE
        NOT


%union {
  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  void *ptr;
  int number;
  float floats;
	char *position;
}

%token <number> NUMBER
%token <floats> FLOAT 
%token <string> ID
%token <string> PATH
%token <string> SSS
%token <string> STAR
%token <string> STRING_V
//非终结符

%type <number> type
%type <number> null_def
%type <number> agg_type
%type <ptr> condition_field
%type <condition1> condition
%type <number> comOp
%type <ptr> subquery
%type <value1> value
%type <number> number
%type <number> order_type
%type <string> ID_list

%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
	  select  
	| insert
	| update
	| delete
	| create_table
	| drop_table
	| show_tables
	| desc_table
	| create_index	
	| drop_index
	| sync
	| begin
	| commit
	| rollback
	| load_data
	| help
	| exit
    ;

exit:			
    EXIT SEMICOLON {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:		/*drop table 语句的语法解析树*/
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

create_index:		/*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID_list RBRACE SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $3, $5);
		}
    | CREATE UNIQUE INDEX ID ON ID LBRACE ID_list RBRACE SEMICOLON
    		{
			CONTEXT->ssql->flag = SCF_CREATE_UNIQUE_INDEX;// "create_unique_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $4, $6);
    		}
    ;

ID_list:
    ID 		{
			create_index_append_attribution(&CONTEXT->ssql->sstr.create_index, $1);
//    			$$ = $1;
    		}
    | ID COMMA ID_list
    		{
    			create_index_append_attribution(&CONTEXT->ssql->sstr.create_index, $1);
//			$$ = $1;
    		}
    ;

drop_index: /*drop index 语句的语法解析树*/
    DROP INDEX ID  SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3);
		}
    ;
create_table:		/*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list {    }
    ;
    
attr_def:
    ID_get type null_def LBRACE number RBRACE
		{
			AttrInfo attribute;
			// 我们让nullable的列增加4个字节
			attr_info_init(&attribute, CONTEXT->id, $2, $5 + $3 * 4, $3);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
    |ID_get type null_def
		{
			AttrInfo attribute;
			// 这里我们可以让nullable的属性列长度增加4个字节
			if ($2 == TEXTS) {
				// TEXTS默认为4096字节
				attr_info_init(&attribute, CONTEXT->id, CHARS, 4096 + $3 * 4, $3);
			} else {
				attr_info_init(&attribute, CONTEXT->id, $2, 4 + $3 * 4, $3);
			}
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
    ;


null_def:
	  { $$ = 0; } // empty
	| NULLABLE_T { $$ = 1; }
	| NOT NULL_T { $$ = 0; }
	;


number:
		NUMBER {$$ = $1;}
		;

type:
	INT_T { $$=INTS; }
       | STRING_T { $$=CHARS; }
       | FLOAT_T { $$=FLOATS; }
       | DATE_T { $$=DATE; }
       | TEXT_T { $$ = TEXTS; }
       ;

agg_type:
	MAX { $$ = AGG_MAX; }
	| MIN { $$ = AGG_MIN; }
	| COUNT { $$ = AGG_COUNT; }
	| AVG { $$ = AGG_AVG; }
	;

order_type:
	ASC {
	$$ = ORDER_ASC; printf("I am ASC\n");}
	| DESC {
	$$ = ORDER_DESC; printf("I am DESC\n");}
	;

ID_get:
	ID 
	{
		char *temp=$1; 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
	;

insert_value_list:
    // empty
    | COMMA LBRACE value value_list RBRACE insert_value_list
    		{

    		}
    ;
insert:	/*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE insert_value_list SEMICOLON
		{
			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, $3, CONTEXT->values, CONTEXT->value_length);

      			//临时变量清零
      			CONTEXT->value_length=0;
    		}

value_list:
    /* empty */
    | COMMA value value_list  { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
    ;
value:
    NUMBER
    		{
  			value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |FLOAT
    		{
  			value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |SSS
    		{
			$1 = substr($1,1,strlen($1)-2);
  			value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    | NULL_T
    		{
    			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    		}
    ;
    
delete:		/*  delete 语句的语法解析树*/
    DELETE FROM ID where SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
    ;

update:			/*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ value where SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, $2, $4, value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
    ;
select:				/*  select 语句的语法解析树*/
    SELECT select_attr FROM ID join_list rel_list where group_by order SEMICOLON
		{
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, $4);
			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
	;

//table:
//	ID join_list
//		{
//			selects_append_relation(&CONTEXT->ssql->sstr.selection, $1);
//		}
//	;

join_list:
	// empty
	| INNER JOIN ID ON condition condition_list join_list
		{
			selects_append_relation(&CONTEXT->ssql->sstr.selection, $3);
		}
	;

select_attr:
    STAR
    		{
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
    | ID attr_list
    		{
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
    | ID DOT ID attr_list
    		{
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
    | agg_type LBRACE STAR RBRACE attr_list
    		{
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, $1, AGG_STAR, NULL, "*");
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
    | agg_type LBRACE number RBRACE attr_list
    		{
			AggDesc agg_desc;
			agg_desc_init_number(&agg_desc, $1, AGG_NUMBER, $3);
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
    | agg_type LBRACE ID RBRACE attr_list
    		{
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, $1, AGG_FIELD, NULL, $3);
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
    | agg_type LBRACE ID DOT ID RBRACE attr_list
    		{
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, $1, AGG_FIELD, $3, $5);
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
    ;

attr_list:
    /* empty */
    | COMMA ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $2);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
    | COMMA ID DOT ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $2, $4);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
	| COMMA agg_type LBRACE STAR RBRACE attr_list
		{
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, $2, AGG_STAR, NULL, "*");
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
	| COMMA agg_type LBRACE number RBRACE attr_list
		{
			AggDesc agg_desc;
			agg_desc_init_number(&agg_desc, $2, AGG_NUMBER, $4);
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
	| COMMA agg_type LBRACE ID RBRACE attr_list
		{
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, $2, AGG_FIELD, NULL, $4);
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
	| COMMA agg_type LBRACE ID DOT ID RBRACE attr_list
		{
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, $2, AGG_FIELD, $4, $6);
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
	;

rel_list:
    /* empty */
    | COMMA ID join_list rel_list
    		{
			selects_append_relation(&CONTEXT->ssql->sstr.selection, $2);
		}
    ;
where:
    /* empty */ 
    | WHERE condition condition_list
    		{
			// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
		}
    ;
condition_list:
    /* empty */
    | AND condition condition_list
    		{
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
		}
    ;

condition_field:
	value {
		$$ = condition_field_init_value(&CONTEXT->values[CONTEXT->value_length - 1]);
	}
	| ID {
		$$ = condition_field_init_attr(NULL, $1);
	}
	| ID DOT ID {
		$$ = condition_field_init_attr($1, $3);
	}
	| LBRACE subquery RBRACE {
		$$ = condition_field_init_subquery($2);
	}
	;

condition:
	condition_field comOp condition_field {
		Condition condition;
		memset(&condition, 0, sizeof(Condition));
		condition_init(&condition, $1, $3, $2);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
	;

subquery:
    SELECT subquery_select_attr FROM ID subquery_join_list subquery_rel_list subquery_where {
			subquery_append_relation(current_subquery(CONTEXT), $4);
			$$ = pop_subquery(CONTEXT);
	}
	;

subquery_select_attr:
	STAR {
			push_subquery(CONTEXT);
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			subquery_set_attribute(current_subquery(CONTEXT), &attr);
	}
	| ID {
			push_subquery(CONTEXT);
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			subquery_set_attribute(current_subquery(CONTEXT), &attr);
	}
	| ID DOT ID {
			push_subquery(CONTEXT);
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			subquery_set_attribute(current_subquery(CONTEXT), &attr);
	}
	| agg_type LBRACE STAR RBRACE {
			push_subquery(CONTEXT);
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, $1, AGG_STAR, NULL, "*");
			subquery_set_agg(current_subquery(CONTEXT), &agg_desc);
	}
	| agg_type LBRACE number RBRACE {
			push_subquery(CONTEXT);
			AggDesc agg_desc;
			agg_desc_init_number(&agg_desc, $1, AGG_NUMBER, $3);
			subquery_set_agg(current_subquery(CONTEXT), &agg_desc);
	}
	| agg_type LBRACE ID RBRACE {
			push_subquery(CONTEXT);
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, $1, AGG_FIELD, NULL, $3);
			subquery_set_agg(current_subquery(CONTEXT), &agg_desc);
	}
   	| agg_type LBRACE ID DOT ID RBRACE {
			push_subquery(CONTEXT);
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, $1, AGG_FIELD, $3, $5);
			subquery_set_agg(current_subquery(CONTEXT), &agg_desc);
	}
	;

subquery_join_list:
	// empty
	| INNER JOIN ID ON subquery_condition subquery_condition_list subquery_join_list {
		subquery_append_relation(current_subquery(CONTEXT), $3);
	}
	;

subquery_rel_list:
    	/* empty */
    	| COMMA ID subquery_join_list subquery_rel_list {
		subquery_append_relation(current_subquery(CONTEXT), $2);
	}
	;

subquery_where:
	/* empty */
     	| WHERE subquery_condition subquery_condition_list {
		// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
	}
   	;

subquery_condition:
	condition_field comOp condition_field {
		Condition condition;
		memset(&condition, 0, sizeof(Condition));
		ConditionField *left = (ConditionField *)$1;
		ConditionField *right = (ConditionField *)$3;
		condition_init(&condition, $1, $3, $2);
		subquery_append_condition(current_subquery(CONTEXT), &condition);
	}
	;

subquery_condition_list:
	/* empty */
    	| AND subquery_condition subquery_condition_list {
		// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
	}
	;

group_by:
	/* empty */
	| GROUP BY ID group_by_attr_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $3);
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| GROUP BY ID DOT ID group_by_attr_list {
		RelAttr attr;
		relation_attr_init(&attr, $3, $5);
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	;

group_by_attr_list:
	/* empty */
	| COMMA ID group_by_attr_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $2);
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
    | COMMA ID DOT ID group_by_attr_list {
		RelAttr attr;
		relation_attr_init(&attr, $2, $4);
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
  	}
  	;

comOp:
    EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | IS { $$ = IS_OP;}
    | IS NOT { $$ = IS_NOT_OP;}
    | IN { $$ = COND_IN; }
    | NOT IN { $$ = NOT_IN; }
    ;

load_data:
		LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON
		{
		  	CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
		}
		;

order:
	/* empty */
	| ORDER BY ID order_type order_attrs
		{
			Order order;
			order_info_init(&order, $4, NULL,$3);
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
	| ORDER BY ID order_attrs
		{
			Order order;
			order_info_init(&order, ASC, NULL, $3);
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
	| ORDER BY ID DOT ID order_attrs
		{
			Order order;
			order_info_init(&order, ASC, $3, $5);
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
	| ORDER BY ID DOT ID order_type order_attrs
		{
			Order order;
			order_info_init(&order, $6, $3, $5);
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
		;
order_attrs:
	/* empty */
	| COMMA ID order_type order_attrs
		{
			Order order;
			printf("odered_type : %d\n", CONTEXT->order_type);
			order_info_init(&order, $3, NULL,$2);
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
	| COMMA ID order_attrs
		{
			Order order;
			order_info_init(&order, ASC, NULL, $2);
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
	| COMMA ID DOT ID order_attrs
		{
			Order order;
			order_info_init(&order, ASC, $2, $4);
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
	| COMMA ID DOT ID order_type order_attrs{
			Order order;
			order_info_init(&order, $5, $2,$4);
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
	;

%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));
	list_init(&context.subquery_list);

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
