;; Function: odd_copy
;; Input parameter: a list
;; Return value: a list containing every other element of the
;;               input list. 
;; Description: Starting with the first value in the input list,
;;              this function will create and return a list
;;              containing every other element of the input
;;              parameter list. 

(define (odd_copy ls)
	(cond ((not (list? ls)) "odd copy requires a list argument")
	      ((null? ls) '())
	      ((null? (cdr ls)) ls)
	      (else (cons (car ls) (odd_copy (cddr ls))))
        )
)

(define (main)
	(display (odd_copy '(1 3 5 7)))
	(newline)
	(display (odd_copy '(1 3 5 7 9)))
	(newline)
)
