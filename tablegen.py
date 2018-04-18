NoRule = 0

#
# Firsts
#

def check_firsts_program( ttype ):
    if check_firsts_define( ttype ):
        return 1
    return NoRule


def check_firsts_define( ttype ):
    if ttype == 'LPAREN_T':
        return 2
    return NoRule


def check_firsts_more_defines( ttype ):
    if check_firsts_define(ttype):
        return 3
    if check_follows_more_defines(ttype):
        return 4
    return NoRule


def check_firsts_stmt( ttype ):
    if check_firsts_literal(ttype):
        return 7
    if ttype == 'IDENT_T':
        return 8
    if ttype == 'LPAREN_T':
        return 9
    return NoRule


def check_firsts_stmt_list( ttype ):
    if check_firsts_stmt(ttype):
        return 5;
    if check_follows_stmt_list(ttype):
        return 6;
    return NoRule;


def check_firsts_literal( ttype ):
    if ttype == 'NUMLIT_T':
        return 10
    if ttype == 'STRLIT_T':
        return 11
    if ttype == 'QUOTE_T':
        return 12
    return NoRule


def check_firsts_quoted_lit( ttype ):
    if check_firsts_aot( ttype ):
        return 13
    return NoRule


def check_firsts_more_tokens( ttype ):
    if check_firsts_aot( ttype ):
        return 14
    if check_follows_more_tokens( ttype ):
        return 15
    return NoRule


def check_firsts_param_list( ttype ):
    if ttype == 'IDENT_T':
        return 16
    if check_follows_param_list( ttype ):
        return 17
    return NoRule


def check_firsts_else_part( ttype ):
    if check_firsts_stmt( ttype ):
        return 18
    if check_follows_else_part( ttype ):
        return 19
    return NoRule


def check_firsts_stmt_pair( ttype ):
    if ttype == 'LPAREN_T':
        return 20
    if check_follows_stmt_pair( ttype ):
        return 21
    return NoRule


def check_firsts_stmt_pair_body( ttype ):
    if check_firsts_stmt( ttype ):
        return 22
    if ttype == 'ELSE_T':
        return 23
    return NoRule


def check_firsts_action( ttype ):
    getrule = { 'IF_T':24, 'COND_T':25, 'LISTOP_T':26,
                'CONST_T':27, 'AND_T':28, 'OR_T':29,
                'NOT_T':30, 'NUMBERP_T':31, 'SYMBOLP_T':32,
                'LISTP_T':33, 'ZEROP_T':34, 'NULLP_T':35,
                'STRINGOP_T':36, 'PLUS_T':37, 'MINUS_T':38,
                'DIV_T':39, 'MULT_T':40, 'MODULO_T':41,
                'EQUALTO_T':42, 'GT_T':43, 'LT_T':44,
                'GTE_T':45, 'LTE_T':46, 'IDENT_T':47,
                'DISPLAY_T':48, 'NEWLINE_T':49}
    if ttype in getrule:
        return getrule[ttype]
    return NoRule


def check_firsts_aot( ttype ):
    getrule = { 'LPAREN_T':50, 'IDENT_T':51, 'NUMLIT_T':52,
                'STRLIT_T':53, 'CONST_T':54, 'IF_T':55,
                'DISPLAY_T':56, 'NEWLINE_T':57,'LISTOP_T':58,
                'AND_T':59, 'OR_T':60, 'NOT_T':61,
                'DEFINE_T':62, 'NUMBERP_T':63,'SYMBOLP_T':64,
                'LISTP_T':65, 'ZEROP_T':66, 'NULLP_T':67,
                'STRINGP_T':68, 'PLUS_T':69, 'MINUS_T':70,
                'DIV_T':71, 'MULT_T':72, 'MODULO_T':73,
                'EQUALTO_T':74, 'GT_T':75, 'LT_T':76,
                'GTE_T':77, 'LTE_T':78, 'QUOTE_T':79,
                'COND_T':80, 'ELSE_T':81}
    if ttype in getrule:
        return getrule[ttype]
    return NoRule

#
# Follows
#

def check_follows_define( ttype ):
    return check_firsts_more_defines( ttype ) != NoRule


def check_follows_more_defines( ttype ):
    return ttype == 'EOF_T'


def check_follows_stmt_list( ttype ):
    return ttype == 'RPAREN_T' or check_follows_action( ttype )


def check_follows_stmt( ttype ):
    if check_firsts_stmt_list( ttype ):
        return True
    return check_follows_else_part( ttype )


def check_follows_literal( ttype ):
    return check_follows_stmt( ttype )


def check_follows_action( ttype):
    return ttype == 'RPAREN_T'


def check_follows_quoted_lit( ttype ):
    return check_follows_literal( ttype )


def check_follows_more_token( ttype ):
    return ttype == 'RPAREN_T'


#TODO double check follows here
def check_follows_param_list( ttype ):
    return ttype == 'RPAREN_T'


def check_follows_else_part( ttype ):
    return check_follows_action( ttype )


def check_follows_stmt_pair( ttype ):
    return check_follows_stmt_pair_body( ttype )


#check_follows_stmt_pair( ttype ) or \
def check_follows_stmt_pair_body( ttype ):
    return check_follows_action( ttype )


def check_follows_aot( ttype ):
    if check_firsts_more_tokens( ttype ):
        return True
    return check_follows_quoted_lit( ttype )


def check_follows_more_tokens( ttype ):
    return ttype == 'RPAREN_T'

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
