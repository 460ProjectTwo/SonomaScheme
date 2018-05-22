;; Project 2 Test Errors


(define (abs1 v)
	(if (> v 0)
		v
		(- 0 v)
	)
)

(define (abs2 v)
	(if (number? v)
		(if (> v 0)
			v
			(- 0 v)
		)
		'NotNumeric
	)
)

(define (arithmetic1 a b c d e)
	(+ (* (+ a b c) (- b d)) (- (* c d e) (/ a e)))
)

(define (square n)
        (if (number? n)
		(* n n)
                'invalid_parameter
        )
)

(define (babylonian s x)
	(if (< (- (square x) s) 0.0000000001)
		x
		(babylonian s (/ (+ x (/ s x)) 2.0))
	)
)

(define (sqrt v)
	(if (< v 4)
		(babylonian v v)
		(babylonian v (/ v 2.0))
	)
)


(define (predicates x)
  	(if (string? x)
		"Is a string"
		(if (null? x)
			"Is null"
			(if (symbol? x)
				"Is a symbol"
				(if (list? x)
					"Is a list"
					(if (zero? x)
						"Is zero"
						(if (number? x)
							"Is a number"
							"Is a USO"
						)
					)
				)
			)
		)
	)
)

(define (iftest a b c)
	(if (and (= a b) (= b c))
		'all_the_same
		(if (not (or (> a b) (> b c)))
			'in_ascending_order
			(if (not (< a c))
				'in_decscending_order
				'three_values_passed
			)
		)
	)
)

(define (insert_last ls v)
        (if (list? ls)
        	(if (null? ls)
                	(cons v '())
                	(cons (car ls) (insert_last (cdr ls) v))
		)
        	'first_argument_of_insert_last_must_be_a_list
	)
)

(define (list_reverse ls)
        (if (list? ls)
            	(if (null? ls)
                	'()
                	(insert_last (list_reverse (cdr ls)) (car ls))
		)
            	'list_reverse_requires_a_list_argument)
)


(define (listop_ex1)
	(cons (car '(a b c)) (cdr '(d e f)))
)

(define (listop_ex2)
	(cons (cadr '(a b c)) (cddr '(d e f)))
)

(define (cond_ex_1 choice value)
    (cond ((= choice 1) value)
	  ((= choice 2) (* value value))
	  ((= choice 3) (if (= value 0)
				"Division by 0 not defined"
				(/ 1 value)
			))
	  (0)
    )
)

(define (reciprocal n)
        (if (and (number? n) (not (= n 0)))
                (/ 1 n)
                'invalid_parameter
        )
)

(define (cond_ex_2 choice value)
    (cond ((= choice 1) value)
	  ((= choice 2) (square value))
	  ((= choice 3) (reciprocal value))
	  (0)
    )
)

(define (main)
	(display (+ (* 1.2 (- 2 (/ 1 3.1))) -8.7)) (newline)
	(display (/ (+ (/ 2 3.2) (/ 2.3 9)) (- (/ 5 1.4) (/ 2 3.5)))) (newline)
	(display (+ 1 (/ 1 (+ 2 (/ 1 (+ 1 (/ 1 2.6))))))) (newline)
	(display (* 1 -2 3 -2 5 -6 7)) (newline)
	(display (* (modulo 10 3) (modulo 3 7))) (newline)
	(display (abs1 5)) (newline)
	(display (abs2 -5)) (newline)
	(display (arithmetic1 1 2 4 8 16)) (newline)
	(display (square 25)) (newline)
	(display (sqrt 4)) (newline)
	(display (listop_ex1)) (newline)
	(display (listop_ex2)) (newline)
	(display (list_reverse '(indentifier numeric literal cons if display newline
        			 cddr and or not define number? symbol? list? zero?
				 null? modulo string? + - / * = > < >= <= 'anything
				 1 1.01 "HelloWorld")))
	(newline)
	(display (predicates 0)) (newline)
	(display (predicates (+ 5 6))) (newline)
	(display (predicates 'hello)) (newline)
	(display (predicates '(a b c))) (newline)
	(display (predicates '())) (newline)
	(display (predicates "hello world")) (newline)
	(display (iftest 10 15 20)) (newline)
	(display (cond_ex_1 1 5.0)) (newline)
	(display (cond_ex_2 1 5.0)) (newline)
	(display (cons 'a 'b)) (newline)
)
