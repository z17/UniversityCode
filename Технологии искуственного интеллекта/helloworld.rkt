#lang racket
(define fact (lambda(x)
               (if (= x 1)
                   x
                   (* x (fact (- x 1)))
                   )))

(define fib (lambda(x)
              (if (< x 2)
                  1
                 (+ (fib (- x 1)) (fib (- x 2))))))

(define (getfib2 n f1 f2)
    (if (< n 2)
        f2
        (getfib2 (- n 1) f2 (+ f1 f2))))

(define fib2 (lambda(x1)
             (getfib2 x1 1 1)))
