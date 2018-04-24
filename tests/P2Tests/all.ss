(define (m) 10)
(define (function var)
    (cond ((list? ls) "is a list")
    )
)
(define (function var)
    (car ls)
)
(define (function var)
    (cons (car ls) ls)
)
(define (function var)
    (AND 1 1)
)
(define (functio1 var)
    (* 2 2)
)

(define (function2 var)
    (* 1 1)
)
(define (abc) 'list?)

(define (a) b)
;;25
(define (a) (cond (ident ident) (else ident )))
;;27
(define (a) (cons '(a) '(b)))
;;29
(define (a) (or))
;;31
(define (a) (numberP ident))
;;33
(define (a) (listP ident))
;;35
(define (a) (nullP ident))
;;37
(define (a) (+))
;;39
(define (a) (/ ident))
;;41
(define (a) (modulo ident ident))
;;43
(define (a) (>))
;;45
(define (a) (>=))
;;47
(define (a) (a))
;;49
(define (a) (newline))
(define (a) '(and)'(zero?)'(else))
(define (last list)
  (cond ((null? (cdr list)) (car list))
	(else (last (cdr list)))
	)
  )
(define (d)
  (- 2))
(define (e)
  (*) )
(define (f)
  (=) )
(define (g)
  (<) )
(define (h)
  (<=))
(define (i)
  (display 'a))
(define (reciprocal n)
  'not
  )
(define (symbolCheck)
  'symbol? a)
(define (function var)
    (cond ((list? ls) "is a list")
    )
)
(define (function var)
    (car ls)
)
(define (function var)
    (cons (car ls) ls)
)
(define (function var)
    (AND 1 1)
)
(define (function var)
    (OR 1 1)
)
(define (function var)
    (NOT (= 1 1))
)
(define (function var)
    (number? 1)
)
(define (function var)
    (symbol? var)
)
(define (function var)
    (list? ls)
)
(define (function var)
    (zero? 0)
)
(define (function var)
    (null? ls)
)
(define (function var)
    (string? "asf")
)
(define (function var)
    (+ 1 1)
)
(define (function var)
    (- 1 1)
)
(define (function var)
    (/ 4 2)
)
(define (function var)
    (* 2 2)
)
(define (function var)
    (modulo 4 2)
)
(define (function var)
    (= 1 1)
)
(define (function var)
    (> 2 1)
)
(define (function var)
    (< 1 2)
)
(define (function var)
    (>= 2 2)
)
(define (function var)
    (<= 2 2)
)
(define (functio1 var)
    (* 2 2)
)

(define (function2 var)
    (* 1 1)
)
(define (function)
    'newline
)
(define (function)
    'string?
)
(define (function)
    ''a
)
; Rule 24
(define (rule_24_a) (if (> 3 4) 2 3))
(define (rule_24_b) (if (< 3 4) 'true 'false))
(define (rule_24_c) (if (null? '()) 'is_null 'not_null))
(define (rule_24_d) (if (zero? '3) 'is_zero 'not_zero))
; Rule 26
(define (rule_26_a) (car '(a)))
(define (rule_26_b) (cdr '(a)))
(define (rule_26_c) (car '((a)b)))
(define (rule_26_d) (cdr '((a)b)))
(define (rule_26_e) (cadr '((a)b)))
(define (rule_26_f) (cddr '((a)b)))
; Rule 28
(define (rule_28_a) (and))
; Rule 30
(define (rule_30_a) (not (< 4 3)))
(define (rule_30_b) (not (and (= 3 3) (< 2 3))))
; Rule 32
(define (rule_32_a) (symbol? 'a))
; Rule 34
(define (rule_34_a) (zero? 0))
; Rule 36
(define (rule_36_a) (string? "hello, world"))
; Rule 38
(define (rule_38_a) (- 4 2))
; Rule 40
(define (rule_40_a) (* 1 2))
(define (rule_40_b) (*))
; Rule 42
(define (rule_42_a) (= 2 2))
(define (rule_42_b) (=))
; Rule 44
(define (rule_44_a) (< 3 4))
(define (rule_44_b) (<))
; Rule 46
(define (rule_46_a) (<= 3 3))
(define (rule_46_b) (<=))
; Rule 48
(define (rule_48_a) (display "0118999\n"))
(define (rule_48_b) (display 0118999))
(define (rules_54_71_76_a arg1 arg2) 
	(if (number? arg1)
		(if (and (> arg1 0) (list? '(< arg1 10)))
			'(cons (/ arg1 2) arg2)
			'()
		)
		"Argument 1 should be a number\n"	
	)
)

;(display (rules_54-71-76_a 4 '(a b c)));; File: S19.ss
;; Authors: Devin Brown and Ryan Moeller

;; Rule 19
;; Rule 73
;; Rule 74
(define (f) (if 'modulo '=))
;; File: S1.ss
;; Authors: Devin Brown and Ryan Moeller

;; Smallest possible program that compiles
(define (x) x)
;; File: S25.ss
;; Authors: Devin Brown and Ryan Moeller

;; Rule 25
(define (x) (cond (x x)))
;; File: S27.ss
;; Authors: Devin Brown and Ryan Moeller

;; Rule 27
(define (x) (cons 0 x))
;; File: S29.ss
;; Authors: Devin Brown and Ryan Moeller

;; Rule 29
(define (x) (or))
;; File: S31.ss
;; Authors: Devin Brown and Ryan Moeller

;; Rule 31
(define (x) (number? x))
;; File: S33.ss
;; Authors: Devin Brown and Ryan Moeller

;; Rule 33
(define (x) (list? x))
;; File: S35.ss
;; Authors: Devin Brown and Ryan Moeller

;; Rule 35
(define (x) (null? x))
;; File: S37.ss
;; Authors: Devin Brown and Ryan Moeller

;; Rule 37
(define (x) (+))
;; File: S39.ss
;; Authors: Devin Brown and Ryan Moeller

;; Rule 39
(define (x) (/ x))
;; File: S41.ss
;; Authors: Devin Brown and Ryan Moeller

;; Rule 41
(define (x) (modulo x x))
;; File: S43.ss
;; Authors: Devin Brown and Ryan Moeller

;; Rule 43
(define (x) (>))
;; File: S45.ss
;; Authors: Devin Brown and Ryan Moeller

;; Rule 45
(define (x) (>=))
;; File: S47.ss
;; Authors: Devin Brown and Ryan Moeller

;; Rule 47
(define (x) (x))
;; File: S49.ss
;; Authors: Devin Brown and Ryan Moeller

;; Rule 49
(define (x) (newline))
;; File: S19.ss
;; Authors: Devin Brown and Ryan Moeller

;; Rule 19
;; Rule 73
;; Rule 74
(define (f) (if 'modulo '=))
(define (isList a) (if (list? a) a 'param_passed_is_not_list)) ;rule 24 ; rule 33(define (carList a) (car a)) ;rule 26(define (PositiveNumber a) (and (number? a) (<= 0 a))) ;rule 28 (define (NotList a) (not (list? a))) ; rule 30;follow actual  structure, all start with define 
(define (isSymbol a) (symbol? a)) ; rule 32(define (isZero a) (zero? a)) ;rule 34(define(isString a) (string? a)) ;rule 36(define(Sub a b) (- a b)) ;rule 38(define(Mult a b) (* a b)) ;rule 40(define(EqaulTo a b) (= a b)) ; rule 42(define(LessThan a b) ( < a b));rule 44(define(LessThanEqual a b) ( <= a b )) ;rule 46(define(DisplayZ a) (display a));rule 48(define (HelloWorld) 'HelloWorld) ; rule53(define (square) '*) ;rule72(define (greater) '>);; File: U25.ss
;; Group U

(define (a)
  (cond (a b)
	(else c)
	)
  )
;; File: U27.ss
;; Group U

(define (a)
  (cons a b)
  )
;; File: U29.ss
;; Group U

(define (a)
  (or b)
  )
;; File: U31.ss
;; Group U

(define (a)
  (number? a)
  )
;; File: U33.ss
;; Group U

(define (a)
  (list? 9)
  )
;; File U35.ss
;; Group U

(define (a)
  (null? 9)
  )
(define (add a b) (+))(define (divide a b) (/ a b))
(define (mod a b)
  (modulo a b)
  )
(define (greater_than a b) (>))(define (greater_equal a b) (>=))(define (ident) (IDENT_T))(define (nwln) (NEWLINE_T))
(define (if_token) 'if)
(define (minus a) '-)
(define (gte_token) '>=)
(define (i) i)(define (j) j)
(define (i) (if i i (i)))
(define (i) (cond (i i)))
(define (i) (car (car (i))))
(define (i) (cons (cons i i) i))
(define (i) (or i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i i))
(define (i j) i j)
(define (i) (not i))
(define (mod i j) (modulo i i))
(define (i) 'display) (define (i) '+) (define (i) '<=)
(define (rule25) (cond ((=) 'yeah ))) 	; Rule 25
(define (rule27) (const '(a) '(b))) 	; Rule 27
(define (rule29) (or)) 		; Rule 29
(define (rule31) (number? 0)) 		; Rule 31
(define (rule33) (list? 0)) 		; Rule 33
(define (rule35) (null? 0)) 		; Rule 35
(define (rule37) (+)) 			; Rule 37
(define (rule39) (/ 1)) 		; Rule 39
(define (rule41) (modulo 5 2)) 	; Rule 41
(define (rule43) (>)) 			; Rule 43
(define (rule45) (>=)) 		; Rule 45
(define (rule47) (this)) 		; Rule 47
(define (rule49) (newline)) 		; Rule 49
(define (rules80) (cons 'car (cons 'null? 'cond )))

(define (a) 10)
(define (a) "a")
(define (a) '2)
(define (a) '2)
(define (a) '())
(define (a) '())
(define (a b) 10)
(define (a) 10)
(define (a) (if 'define 'number?))
