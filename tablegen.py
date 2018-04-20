Rule = int
Token = str
NoRule: Rule = 0

#
# Firsts
#

def check_firsts_program( token: Token ) -> Rule:
    if check_firsts_define( token ):
        return 1
    return NoRule


def check_firsts_define( token: Token ) -> Rule:
    if token == 'LPAREN_T':
        return 2
    return NoRule


def check_firsts_more_defines( token: Token ) -> Rule:
    if check_firsts_define(token):
        return 3
    if check_follows_more_defines(token):
        return 4
    return NoRule


def check_firsts_stmt( token: Token ) -> Rule:
    if check_firsts_literal(token):
        return 7
    if token == 'IDENT_T':
        return 8
    if token == 'LPAREN_T':
        return 9
    return NoRule


def check_firsts_stmt_list( token: Token ) -> Rule:
    if check_firsts_stmt(token):
        return 5;
    if check_follows_stmt_list(token):
        return 6;
    return NoRule;


def check_firsts_literal( token: Token ) -> Rule:
    if token == 'NUMLIT_T':
        return 10
    if token == 'STRLIT_T':
        return 11
    if token == 'QUOTE_T':
        return 12
    return NoRule


def check_firsts_quoted_lit( token: Token ) -> Rule:
    if check_firsts_aot( token ):
        return 13
    return NoRule


def check_firsts_more_tokens( token: Token ) -> Rule:
    if check_firsts_aot( token ):
        return 14
    if check_follows_more_tokens( token ):
        return 15
    return NoRule


def check_firsts_param_list( token: Token ) -> Rule:
    if token == 'IDENT_T':
        return 16
    if check_follows_param_list( token ):
        return 17
    return NoRule


def check_firsts_else_part( token: Token ) -> Rule:
    if check_firsts_stmt( token ):
        return 18
    if check_follows_else_part( token ):
        return 19
    return NoRule


def check_firsts_stmt_pair( token: Token ) -> Rule:
    if token == 'LPAREN_T':
        return 20
    if check_follows_stmt_pair( token ):
        return 21
    return NoRule


def check_firsts_stmt_pair_body( token: Token ) -> Rule:
    if check_firsts_stmt( token ):
        return 22
    if token == 'ELSE_T':
        return 23
    return NoRule


def check_firsts_action( token: Token ) -> Rule:
    getrule = { 'IF_T':24, 'COND_T':25, 'LISTOP_T':26,
                'CONS_T':27, 'AND_T':28, 'OR_T':29,
                'NOT_T':30, 'NUMBERP_T':31, 'SYMBOLP_T':32,
                'LISTP_T':33, 'ZEROP_T':34, 'NULLP_T':35,
                'STRINGP_T':36, 'PLUS_T':37, 'MINUS_T':38,
                'DIV_T':39, 'MULT_T':40, 'MODULO_T':41,
                'EQUALTO_T':42, 'GT_T':43, 'LT_T':44,
                'GTE_T':45, 'LTE_T':46, 'IDENT_T':47,
                'DISPLAY_T':48, 'NEWLINE_T':49}
    if token in getrule:
        return getrule[token]
    return NoRule


def check_firsts_aot( token: Token ) -> Rule:
    getrule = { 'LPAREN_T':50, 'IDENT_T':51, 'NUMLIT_T':52,
                'STRLIT_T':53, 'CONS_T':54, 'IF_T':55,
                'DISPLAY_T':56, 'NEWLINE_T':57,'LISTOP_T':58,
                'AND_T':59, 'OR_T':60, 'NOT_T':61,
                'DEFINE_T':62, 'NUMBERP_T':63,'SYMBOLP_T':64,
                'LISTP_T':65, 'ZEROP_T':66, 'NULLP_T':67,
                'STRINGP_T':68, 'PLUS_T':69, 'MINUS_T':70,
                'DIV_T':71, 'MULT_T':72, 'MODULO_T':73,
                'EQUALTO_T':74, 'GT_T':75, 'LT_T':76,
                'GTE_T':77, 'LTE_T':78, 'QUOTE_T':79,
                'COND_T':80, 'ELSE_T':81}
    if token in getrule:
        return getrule[token]
    return NoRule

#
# Follows
#

def check_follows_define( token: Token ) -> bool:
    return check_firsts_more_defines( token ) != NoRule


def check_follows_more_defines( token: Token ) -> bool:
    return token == 'EOF_T'


def check_follows_stmt_list( token: Token ) -> bool:
    return token == 'RPAREN_T' or check_follows_action( token )


def check_follows_stmt( token: Token ) -> bool:
    if check_firsts_stmt_list( token ):
        return True
    return check_follows_else_part( token )


def check_follows_literal( token: Token ) -> bool:
    return check_follows_stmt( token )


def check_follows_action( token: Token ) -> bool:
    return token == 'RPAREN_T'


def check_follows_quoted_lit( token: Token ) -> bool:
    return check_follows_literal( token )


def check_follows_more_token( token: Token ) -> bool:
    return token == 'RPAREN_T'


#TODO double check follows here
def check_follows_param_list( token: Token ) -> bool:
    return token == 'RPAREN_T'


def check_follows_else_part( token: Token ) -> bool:
    return check_follows_action( token )


def check_follows_stmt_pair( token: Token ) -> bool:
    return check_follows_stmt_pair_body( token )


#check_follows_stmt_pair( token ) or \
def check_follows_stmt_pair_body( token: Token ) -> bool:
    return check_follows_action( token )


def check_follows_aot( token: Token ) -> bool:
    if check_firsts_more_tokens( token ):
        return True
    return check_follows_quoted_lit( token )


def check_follows_more_tokens( token: Token ) -> bool:
    return token == 'RPAREN_T'

#
# Entry point
#

def main():
    TokenType = [
        "LAMBDA", "IDENT_T", "NUMLIT_T", "STRLIT_T", "CONS_T", "IF_T", "COND_T",
        "DISPLAY_T", "NEWLINE_T", "LISTOP_T", "AND_T", "OR_T", "NOT_T",
        "DEFINE_T", "NUMBERP_T", "SYMBOLP_T", "LISTP_T", "ZEROP_T","NULLP_T",
        "STRINGP_T", "MODULO_T", "ELSE_T", "PLUS_T", "MINUS_T",
        "DIV_T", "MULT_T", "EQUALTO_T", "GT_T", "LT_T", "GTE_T", "LTE_T",
        "LPAREN_T", "RPAREN_T", "QUOTE_T", "ERROR_T", "EOF_T"
    ]
    NTChecks = [
        check_firsts_program, check_firsts_define, check_firsts_more_defines,
        check_firsts_stmt_list, check_firsts_stmt, check_firsts_literal,
        check_firsts_quoted_lit, check_firsts_more_tokens, check_firsts_param_list,
        check_firsts_else_part, check_firsts_stmt_pair, check_firsts_stmt_pair_body,
        check_firsts_action, check_firsts_aot
    ]

    first_rules = [ [ check(t) for t in TokenType ] for check in NTChecks ]
    first_string = str(first_rules)\
        .replace('[[','{\n\t{').replace('[','{').replace('], ','},\n\t')\
        .replace(']]','}\n};')
    print('static rule const rules[][MAX_TOKENS] =', first_string)

if __name__ == "__main__":
    main()
