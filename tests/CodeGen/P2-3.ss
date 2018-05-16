(define (reciprocal n)
        (if (and (number? n) (not (= n 0)))
                (/ 1 n)
                'invalid_parameter
        )
)

(define (main)
        (display (reciprocal 7)) (newline)
)
