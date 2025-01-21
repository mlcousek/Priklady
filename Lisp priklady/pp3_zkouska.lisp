;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;           TAB SHAPE - PP3 zkouska
;;;                                                 Mlcousek Jiri
;;;       

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defclass switchable-shape (picture)
  ((active-item-index :initform '())
   (active-item :initform '())
   (new-items :initform '())))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defmethod new-items ((ss switchable-shape)) 
  (slot-value ss 'new-items))

(defmethod active-item-index ((ss switchable-shape)) 
  (slot-value ss 'active-item-index))

(defmethod do-set-active-item-index ((ss switchable-shape) value)
  (setf (slot-value ss 'active-item-index) value))

(defmethod set-active-item-index ((ss switchable-shape) value) 
  (set-items1 ss (nth value (new-items ss))))
  
(defmethod active-item ((ss switchable-shape)) 
  (slot-value ss 'active-item))

(defmethod do-set-active-item ((ss switchable-shape) value)
  (setf (slot-value ss 'active-item) value)
  (do-set-active-item-index ss (find-item ss)))

(defmethod do-set-items ((ss switchable-shape) value)
  (setf (slot-value ss 'new-items) (copy-list value))
  (send-to-items ss 'set-delegate ss))

(defmethod set-items1 ((ss switchable-shape) value)
  (check-items ss (list value))
  (send-with-change ss 'do-set-items1 (list value))
  (do-set-active-item ss value)
  ss)

(defmethod do-set-items1 ((ss switchable-shape) value)
  (setf (slot-value ss 'items) (copy-list value))
  (send-to-items ss 'set-delegate ss))

(defun find-item (ss)
 (find-item-help 0 (new-items ss) (active-item ss)))

(defun find-item-help (help-number list item)
  (if (eql item (first list))
      help-number
    (find-item-help (1+ help-number) (cdr list) item)))
           
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;; TAB SHAPE

(defclass tab-shape (picture)
  ((switchable-shape :initform '())
   (buttons :initform '())))

(defmethod switchable-shape ((ts tab-shape)) 
  (slot-value ts 'switchable-shape))

(defmethod do-set-switchable-shape ((ts tab-shape) value)
  (setf (slot-value ts 'switchable-shape) value))

(defmethod set-switchable-shape ((ts tab-shape) value) 
  (send-with-change ts 'do-set-switchable-shape value)
  (do-set-buttons ts (create-buttons ts (buttons-count ts)))
  (do-set-items ts (append (buttons ts) (list (switchable-shape ts)))))

(defmethod buttons ((ts tab-shape)) 
  (slot-value ts 'buttons))

(defmethod do-set-buttons ((ts tab-shape) value)
  (setf (slot-value ts 'buttons) value)
  (send-to-buttons ts 'set-delegate ts))

(defmethod buttons-count ((ts tab-shape))
  (when (switchable-shape ts)
    (length (new-items (switchable-shape ts)))))

(defun create-button (ss x y)
   (set-delegate ss (add-event (set-button-text (move (make-instance 'button) x y) '"OBJEKT") 'ev-button-click 'ev-click)))

(defun create-buttons (ss count)
  (create-buttons-help ss count '()))

(defun create-buttons-help (ss count buttons)
  (if (eql count 0) 
      buttons
    (create-buttons-help ss (1- count) (append buttons (list (create-button ss (* count 70) 30))))))

(defmethod send-to-buttons ((shape tab-shape) 
			  message
			  &rest arguments)
  (dolist (button (buttons shape))
    (apply message button arguments))
  shape)

(defmethod ev-click ((ts tab-shape) sender)
    (set-all-buttons-bgr ts ':light-blue)
    (set-button-background-color sender :red)
    (set-items1 (switchable-shape ts) (nth (find-nth-button ts sender) (new-items (switchable-shape ts)))))

(defun find-nth-button (ts button)
 (find-item-help-b 0 (buttons ts) button))

(defun find-item-help-b (help-number list item)
  (if (eql item (first list))
      help-number
    (find-item-help (1+ help-number) (cdr list) item)))

(defmethod set-all-buttons-bgr ((ts tab-shape) color)
  (send-to-buttons ts 'set-button-background-color color))


  
  


#|

setf ss (set-items (make-instance 'switchable-shape) (list (move (set-color (set-filledp (set-radius (make-instance 'circle) 25) t) :gold) 50 100)                               
                                                           (move (set-color (set-filledp (set-radius (make-instance 'circle) 25) t) :blue) 120 150)
                                                           (move (set-color (set-filledp (set-radius (make-instance 'circle) 25) t) :green) 100 120)
                                                           (move (set-color (set-filledp (set-radius (make-instance 'circle) 25) t) :red) 50 120)))  
setf w (make-instance 'window)

setf ts (set-switchable-shape (make-instance 'tab-shape) ss)

set-shape w ts


|#

#|
Co bych upravil, kdybych měl více času: - prošel bych text a lépe popsal některé funkce a rozdělil si některé funkce do více funkcí
                                        - dodělal bych, že když 2x kliknu na objekt tak tam zůstane místo toho, aby se mi tam nastavilo prázdné okno 
                                        - lépe bych rozdělil kód do částí, které s sebou souvisí 
                                        . . .
|#