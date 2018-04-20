;; File: S19.ss
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
