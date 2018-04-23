from functools import lru_cache, wraps

Rule = int
Token = str
NoRule: Rule = 0

# NOTE: All checks must be defined in the correct non-terminal rule order!

#
# Firsts
#

FirstsChecks = []
def check_firsts(f):
    @wraps(f)
    @lru_cache(maxsize=None)
    def wrapper(token: Token) -> Rule:
        return f(token)
    FirstsChecks.append(wrapper)
    return wrapper


@check_firsts
def check_firsts_program( token: Token ) -> Rule:
    if check_firsts_define( token ):
        return 1
    return NoRule


@check_firsts
def check_firsts_define( token: Token ) -> Rule:
    if token == 'LPAREN_T':
        return 2
    return NoRule


@check_firsts
def check_firsts_more_defines( token: Token ) -> Rule:
    if check_firsts_define(token):
        return 3
    if check_follows_more_defines(token):
        return 4
    return NoRule


@check_firsts
def check_firsts_stmt_list( token: Token ) -> Rule:
    if check_firsts_stmt(token):
        return 5;
    if check_follows_stmt_list(token):
        return 6;
    return NoRule;


@check_firsts
def check_firsts_stmt( token: Token ) -> Rule:
    if check_firsts_literal(token):
        return 7
    if token == 'IDENT_T':
        return 8
    if token == 'LPAREN_T':
        return 9
    return NoRule


@check_firsts
def check_firsts_literal( token: Token ) -> Rule:
    if token == 'NUMLIT_T':
        return 10
    if token == 'STRLIT_T':
        return 11
    if token == 'QUOTE_T':
        return 12
    return NoRule


@check_firsts
def check_firsts_quoted_lit( token: Token ) -> Rule:
    if check_firsts_aot( token ):
        return 13
    return NoRule


@check_firsts
def check_firsts_more_tokens( token: Token ) -> Rule:
    if check_firsts_aot( token ):
        return 14
    if check_follows_more_tokens( token ):
        return 15
    return NoRule


@check_firsts
def check_firsts_param_list( token: Token ) -> Rule:
    if token == 'IDENT_T':
        return 16
    if check_follows_param_list( token ):
        return 17
    return NoRule


@check_firsts
def check_firsts_else_part( token: Token ) -> Rule:
    if check_firsts_stmt( token ):
        return 18
    if check_follows_else_part( token ):
        return 19
    return NoRule


@check_firsts
def check_firsts_stmt_pair( token: Token ) -> Rule:
    if token == 'LPAREN_T':
        return 20
    if check_follows_stmt_pair( token ):
        return 21
    return NoRule


@check_firsts
def check_firsts_stmt_pair_body( token: Token ) -> Rule:
    if check_firsts_stmt( token ):
        return 22
    if token == 'ELSE_T':
        return 23
    return NoRule


@check_firsts
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


@check_firsts
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

FollowsChecks = []
def check_follows(f):
    @wraps(f)
    @lru_cache(maxsize=None)
    def wrapper(token: Token) -> bool:
        return f(token)
    FollowsChecks.append(wrapper)
    return wrapper


@check_follows
def check_follows_program( token: Token ) -> bool:
    return token == 'EOF_T'


@check_follows
def check_follows_define( token: Token ) -> bool:
    return check_firsts_more_defines( token ) != NoRule


@check_follows
def check_follows_more_defines( token: Token ) -> bool:
    return token == 'EOF_T'


@check_follows
def check_follows_stmt_list( token: Token ) -> bool:
    return token == 'RPAREN_T' or check_follows_action( token )


@check_follows
def check_follows_stmt( token: Token ) -> bool:
    if check_firsts_stmt_list( token ):
        return True
    return check_follows_else_part( token )


@check_follows
def check_follows_literal( token: Token ) -> bool:
    return check_follows_stmt( token )


@check_follows
def check_follows_quoted_lit( token: Token ) -> bool:
    return check_follows_literal( token )


@check_follows
def check_follows_more_tokens( token: Token ) -> bool:
    return token == 'RPAREN_T'


#TODO double check follows here
@check_follows
def check_follows_param_list( token: Token ) -> bool:
    return token == 'RPAREN_T'


@check_follows
def check_follows_else_part( token: Token ) -> bool:
    return check_follows_action( token )


@check_follows
def check_follows_stmt_pair( token: Token ) -> bool:
    return check_follows_stmt_pair_body( token )


#check_follows_stmt_pair( token ) or \
@check_follows
def check_follows_stmt_pair_body( token: Token ) -> bool:
    return check_follows_action( token )


@check_follows
def check_follows_action( token: Token ) -> bool:
    return token == 'RPAREN_T'


@check_follows
def check_follows_aot( token: Token ) -> bool:
    if check_firsts_more_tokens( token ):
        return True
    return check_follows_quoted_lit( token )

#
# Terminal Tokens
#

TokenType = [
    'LAMBDA',    #  0
    'IDENT_T',   #  1
    'NUMLIT_T',  #  2
    'STRLIT_T',  #  3
    'CONS_T',    #  4
    'IF_T',      #  5
    'COND_T',    #  6
    'DISPLAY_T', #  7
    'NEWLINE_T', #  8
    'LISTOP_T',  #  9
    'AND_T',     # 10
    'OR_T',      # 11
    'NOT_T',     # 12
    'DEFINE_T',  # 13
    'NUMBERP_T', # 14
    'SYMBOLP_T', # 15
    'LISTP_T',   # 16
    'ZEROP_T',   # 17
    'NULLP_T',   # 18
    'STRINGP_T', # 19
    'MODULO_T',  # 20
    'ELSE_T',    # 21
    'PLUS_T',    # 22
    'MINUS_T',   # 23
    'DIV_T',     # 24
    'MULT_T',    # 25
    'EQUALTO_T', # 26
    'GT_T',      # 27
    'LT_T',      # 28
    'GTE_T',     # 29
    'LTE_T',     # 30
    'LPAREN_T',  # 31
    'RPAREN_T',  # 32
    'QUOTE_T',   # 33
    'ERROR_T',   # 34
    'EOF_T'      # 35
]

#
# C++ Utilities
#

def array_initializer(l: list) -> str:
    return str(l).replace('[[','{\n\t{')  \
                 .replace('[','{')        \
                 .replace('], ','},\n\t') \
                 .replace(']]','}\n};')

def bitmask_initializer(l: list) -> str:
    l1 = [ hex(sum(bit << i for (i, bit) in enumerate(row))) + 'ULL' for row in l]
    return str(l1).replace('[','{\n\t')  \
                  .replace(', ',',\n\t') \
                  .replace(']','\n};')   \
                  .replace("'",'')

#
# Entry point
#

def main():
    firsts_rules = [ [ check(t) for t in TokenType ] for check in FirstsChecks ]
    with open('firsts.hpp', 'w') as f:
        f.write('static rule const firsts[][MAX_TOKENS] = ')
        f.write(array_initializer(firsts_rules))

    follows_rules = [ [ 1 if check(t) else 0 for t in TokenType ] for check in FollowsChecks ]
    with open('follows.hpp', 'w') as f:
        f.write('static uint64_t const follows[] = ')
        f.write(bitmask_initializer(follows_rules))

if __name__ == "__main__":
    main()
