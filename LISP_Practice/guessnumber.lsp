;;;;http://www.linuxforu.com/2011/06/lisp-tears-of-joy-part-1/
(defvar *min* 0)
(defvar *max* 101)
(defvar *currentguess* 0)

(defun guessnumber ()
	(picknumber)
)

(defun picknumber ()
	(setq *currentguess* (ash (+ *max* *min*) -1))
)

(defun bigger ()
	(setq *min* (+ *currentguess* 1))
	(guessnumber)
)

(defun smaller ()
	(setq *max* (- *currentguess* 1))
	(guessnumber)
)
