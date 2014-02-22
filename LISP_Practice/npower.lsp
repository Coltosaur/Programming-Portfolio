;;;; the non-recursive version of x to the power y
(defun npower (x y)
	(let ((result x))
		(cond ((= y 0) (setq x 1))
			((= y 1) x)
			((> y 1) 
				(dotimes (i (- y 1))
					(setq x (* x result))
					(print x)
				)
			)
		)
	)
x
)

