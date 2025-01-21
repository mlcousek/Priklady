;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;                                                     ;;;
;;;             UKOL 3 (INSPECTOR)                      ;;;
;;;                                                     ;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                 Jiří Mlčoušek
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;           IW             ;;;;;;;;;;;;;;;;;;;;

(defclass inspector-window (window)
  ((inspected-window :initform '())
   (inspected-object :initform '())))

(defclass inspected-window (inspector-window)
  ())

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defmethod inspected-window ((iw inspector-window)) 
  (slot-value iw 'inspected-window))
#|

(defmethod do-set-inspected-window ((iw inspector-window) value)
  (setf (slot-value iw 'inspected-window) value)
  (set-delegate (inspected-window iw) iw))
|#

(defmethod do-set-inspected-window ((iw inspector-window) value)
  (setf (slot-value iw 'inspected-window) value)
  (add-event (inspected-window iw) 'ev-change 'ev-inspector-change)
  (if value
      (set-delegate (inspected-window iw) iw)
    (progn (do-set-inspected-object iw value) (set-shape iw value))))
      

(defmethod insp-m-for-setting-iw ((iw inspector-window))
  (when (eql (type-of iw) 'INSPECTOR-WINDOW)
      (let ((pic (make-instance 'picture)))
          (prop-fun iw (properties (inspected-window iw)) 50 pic))))

(defmethod set-inspected-window ((iw inspector-window) value) 
  (send-with-change iw 'do-set-inspected-window value)
  (when value 
  (insp-m-for-setting-iw iw))
  iw)

(defmethod inspected-object ((iw inspector-window)) 
  (slot-value iw 'inspected-object))

(defmethod do-set-inspected-object ((iw inspector-window) value)
  (setf (slot-value iw 'inspected-object) value))
      
(defmethod insp-m-for-mouse-down ((iw inspector-window))
  (when (eql (type-of iw) 'INSPECTOR-WINDOW)
      (let ((pic (make-instance 'picture)))
          (prop-fun iw (properties (inspected-object (inspected-window iw)) 50 pic)))))

(defun prop-fun (iw props t1y pic)
  (if (eql props '())
      nil
    (let ((text1 (make-instance 'text-shape))
          (text2 (make-instance 'text-shape)))
        (set-text text1 (tisk (cadar props)))
        (move text1 130 t1y)
        (set-text text2 (caar props))
        (move text2 10 t1y)
        (set-items pic (append (items pic) (list text2 text1)))
        (set-shape iw pic)
        (prop-fun iw (cdr props) (+ t1y 20) pic))))

(defmethod mouse-down-no-shape ((iw inspected-window) button position)
  (ev-mouse-down iw iw iw button position)
  (call-next-method))

(defmethod ev-mouse-down((iw inspected-window) sender clicked button position)
  (do-set-inspected-object iw clicked)
  (insp-m-for-mouse-down (delegate iw))
  (call-next-method))

#|
(defmethod ev-mouse-down((iw inspected-window) sender clicked button position)
  (do-set-inspected-object (delegate iw) clicked)
  (insp-m-for-mouse-down (delegate iw))
  (call-next-method))
|#

(defmethod ev-inspector-change((iw inspector-window) sender)
  (send-with-change iw 'insp-m-for-mouse-down))
  
 


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;          UPRAVA KNIHOVNY (abych mohl vklidu vypsat vlastnosti)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defmethod properties ((sh shape))
  (list (list "CLASS" (type-of sh))
        (list "COLOR" (color sh))
        (list "THICKNESS" (thickness sh))
        (list "FILLEDP" (filledp sh))))

(defmethod properties ((c circle))
  (append (call-next-method)
  (list (list "RADIUS" (radius c)))))
       ; (list "CENTER_X" (x (center c)))
       ; (list "CENTER_Y" (y (center c))))))

(defmethod properties ((p abstract-polygon))
  (append (call-next-method)
  (list (list "CLOSEDP" (closedp p)))))

(defmethod properties ((w abstract-window))
  (list (list "CLASS" (type-of w))
        (list "BACKGROUND" (background w))
        (list "SHAPE" (shape w))))




;;;;;;;;;;;;;;;; DOUBLECLICK

(defmethod install-double-click-callback ((w abstract-window))
  (mg:set-callback 
   (slot-value w 'mg-window) 
   :double-click (lambda (mgw button x y)
                    (declare (ignore mgw))
                    (window-double-mouse-down 
                     w
                     button 
                     (move (make-instance 'point) x y)))))

(defmethod add-double-click ((obj omg-object))
 (add-event obj 'ev-double-click 'ev-double-click))

(defmethod install-callbacks1 ((w abstract-window))
  (install-double-click-callback w))

(defmethod initialize-instance ((iw inspector-window) &key)
  (call-next-method)
  (install-callbacks1 iw)
  (add-double-click iw)
  iw)

(defmethod ev-double-click ((obj inspector-window) sender clicked button position)
  (let ((nth-item (nth-txts (items obj) clicked 0)))
    (send-event obj 'ev-double-click clicked button position)
    (if (eql (type-of clicked) 'TEXT-SHAPE) 
        (if (iwindp clicked)
            (if (oddp nth-item)
                (if (not (string= (text (nth (- nth-item 1) (items obj))) "CLASS"))
                    (funcall (setter-name (text (nth (- nth-item 1) (items obj)))) 
                             (if (inspected-object (inspected-window (go-to-iw clicked)))
                                 (inspected-object (inspected-window (go-to-iw clicked)))
                               (inspected-window (go-to-iw clicked)))
                             (car (multiple-value-list (capi:prompt-for-value "Zadejte novou hodnotu"))))))))))

#|

(defmethod ev-double-click ((obj omg-object) sender clicked button position)
  (let ((nth-item (nth-txts (items obj) clicked 0)))
    (send-event obj 'ev-double-click clicked button position)
    (if (eql (type-of clicked) 'TEXT-SHAPE)
        (if (iwindp clicked)
            (if (oddp nth-item)
                (funcall (setter-name (text (nth (- nth-item 1) (items obj)))) 
                         (if (inspected-object (go-to-iw clicked))
                             (inspected-object (go-to-iw clicked))
                           (inspected-window (go-to-iw clicked)))
                         (car (multiple-value-list (capi:prompt-for-value "Zadejte novou hodnotu")))))))))

|#

(defun nth-txts (obj-items clicked val)
  (if (eql clicked (car obj-items))
      val
    (nth-txts (cdr obj-items) clicked (1+ val))))

(defun iwindp (obj)
  (if (delegate obj)
      (if (eql (type-of (delegate obj)) 'INSPECTOR-WINDOW)
          t
        (iwindp (delegate obj)))
    nil))

(defun go-to-iw (obj)
  (if (delegate obj)
      (let ((del (delegate obj)))
        (if (eql (type-of del) 'INSPECTOR-WINDOW)
            del
          (go-to-iw del)))
    (error "CHYBA")))

(defmethod window-double-mouse-down ((w abstract-window) button position)
  (let ((shape (find-clicked-shape w position)))
    (if shape
        (double-click-inside-shape w shape button position)
      (double-click-no-shape w button position))))

(defmethod double-mouse-down ((shape shape) button position)
  (add-double-click shape)
  (send-event shape 'ev-double-click shape button position))

(defmethod double-click-inside-shape ((iw abstract-window) shape button position)
  (double-mouse-down shape button position)
  iw)


(defmethod double-click-no-shape ((iw abstract-window) button position)
  iw)


;;;;;;;;;;;;;;;;; TISK ;;;;;;;;;;;;;;;;;

(defun tisk (hodnota)
  (format nil "~a" hodnota))

(defun setter-name (prop)
  (values (find-symbol (format nil "SET-~a" prop))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;     TEXT

;       pokud přidám novou třídu do grafické knihovny a moje nová třída bude potomkem nějaké mé třídy z grafické knihovny a chci si přidat svou další vlastnost tak napíši metodu properities př: 
#|

(defmethod properties ((nc new-class))
  (append (call-next-method)
          (list (list "Název vlastnosti" (vlastnost nc)))))
Název vlastnosti musí mít setter s názvem set-název=vlastnosti

|#
; název classy je zakázané editovat, stejně tak i některé jiné vlastnosti jako třeba vlastnost center_x
;pokud bych chtěli aby center_x fungovalo tak si musíme dodefinovat metodu s názvem set-center_x

;třeba takto:
#|

(defmethod set-center_x ((c circle) val)
  (set-x (center c) val))

teď nám bude center_x fungovat


|#




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#|
                                  TESTY

setf inspector (make-instance 'inspector-window)

setf iw (make-instance 'inspected-window)

setf c (move (set-filledp (set-radius (make-instance 'circle) 50) t) 100 100)

setf c1 (move (set-filledp (set-radius (make-instance 'circle) 25) t) 170 100)

setf c2 (set-color (move (set-filledp (set-radius (make-instance 'circle) 25) t) 100 170) :blue)

setf p (set-items (make-instance 'polygon) (list (move (make-instance 'point) 170 170)
                                                 (move (make-instance 'point) 180 170)
                                                 (move (make-instance 'point) 180 180)
                                                 (move (make-instance 'point) 170 180)))
set-filledp p t

setf text1 (make-instance 'text-shape)
        
        (set-text text1 "PROSIM")
        (move text1 130 50)

setf pic (make-instance 'picture)

set-items pic (list c c1 c2 p text1)

set-shape iw pic

set-inspected-window inspector iw



|#
