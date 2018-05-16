(define (square n)
        (if (number? n)
                (* n n)
                'invalid_parameter
        )
)

(define (reciprocal n)
        (if (and (number? n) (not (= n 0)))
                (/ 1 n)
                'invalid_parameter
        )
)

(define (cond_ex_3 choice value)
   (cond	((= choice 1) value)
          ((= choice 2) (square value))
          ((= choice 3) (reciprocal value))
          (else 0)
   )
)

(define (main)
        (display (cond_ex_3 1 5)) (newline)
)
