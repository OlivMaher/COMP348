;; Provides menu and processes user input

(ns fido
  (:require [clojure.string :as str])
  (:require [clojure.java.io :as io]))
  ; this is where you would include/require the food module

;;-------------------
;; THE MENU FUNCTIONS
;; ------------------

;; Display the menu and ask the user for the option
(defn showMenu
  []
  (println "\n\n*** Let's Feed Fido ***")
  (println     "-----------------------\n")
  (println "1. Display list of map files")
  (println "2. Display a map for Fido")
  (println "3. Exit")
  (do 
    (print "\nEnter an option? ") 
    (flush) 
    (read-line)))


;; Display all .txt files in the current folder
(defn option1
  []
  (println "Map List:")
  (let [root (io/file "C:\\Users\\olima\\dev\\COMP348\\A3\\src\\")
        files (file-seq root)
        txt-files (filter #(str/ends-with? (.getName %) ".txt") files)]
    (doseq [file txt-files]
      (println "* ./"(.getName file))))
  (do 
    (print "\nPress any key to continue ") 
    (flush) 
    (read-line)))
    
    
;; Get the map specified by the user and start looking for the food
(defn option2
  []
  (print "\nPlease enter a file name => ") 
  (flush)
  (let [file-name (read-line)
        file-path (str "C:\\Users\\olima\\dev\\COMP348\\A3\\src\\" file-name)
        file (io/file file-path)]
    (if (and (.exists file) (str/ends-with? file-name ".txt"))
      (do (println "\nThis is Fido's challenge\n")
          (println (slurp file-name)))
      (println "Oops: specified file " file-name "does not exist or is not a .txt file")))
  (do 
    (print "\nPress any key to continue ") 
    (flush) 
    (read-line))
)
    



; If the menu selection is valid, call the relevant function to 
; process the selection
(defn processOption
  [option] 
  (if( = option "1")
     (option1)
     (if( = option "2")
        (option2)   
        (println "Invalid menu option")))
  ;(print (str (char 27) "[2J")) ) ; Clears screen
)

; Display the menu and get a menu item selection. Process the
; selection and then loop again to get the next menu selection
(defn menu
  [] ; parm(s) can be provided here, if needed
  (let [option (str/trim (showMenu))]
    (if (= option "3")
      (println "\nGood Bye\n")
      (do 
         (processOption option)
         (recur )))))   



; ------------------------------
; Run the program.
(menu)

