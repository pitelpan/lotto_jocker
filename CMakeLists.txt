# Ορίζει την ελάχιστη έκδοση του CMake που απαιτείται
cmake_minimum_required(VERSION 3.10)

# Ορίζει το όνομα του έργου
project(LotteryGenerator C)

# Ορίζει το πρότυπο της C που θα χρησιμοποιηθεί
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Ορίζει το όνομα του εκτελέσιμου αρχείου
set(EXECUTABLE_NAME lottery)

# Ορίζει τα αρχεία πηγής
set(SOURCE_FILES 
    main.c
)

# Δημιουργεί το εκτελέσιμο
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

# -----------------------------------------------
# ΝΕΕΣ ΕΝΤΟΛΕΣ ΕΓΚΑΤΑΣΤΑΣΗΣ (INSTALL)
# -----------------------------------------------

# 1. Εγκατάσταση του Εκτελέσιμου
# Αντιγράφει το εκτελέσιμο (lottery) στον κατάλογο bin/ του συστήματος.
# Το DESTINATION bin σημαίνει ότι θα εγκατασταθεί στο ${CMAKE_INSTALL_PREFIX}/bin.
install(TARGETS ${EXECUTABLE_NAME}
    DESTINATION bin
)

# 2. Εγκατάσταση της Άδειας Χρήσης (GPLv3)
# Αντιγράφει το αρχείο LICENSE στον κατάλογο share/doc/${PROJECT_NAME} του συστήματος.
# ΠΡΟΣΟΧΗ: Υποθέτουμε ότι υπάρχει αρχείο με όνομα LICENSE στον φάκελο του έργου.
install(FILES LICENSE
    DESTINATION share/doc/${PROJECT_NAME}
)

# 3. Εγκατάσταση του αρχείου πηγής (Προαιρετικό, χρήσιμο για GPL)
# Αντιγράφει το αρχείο πηγής στον κατάλογο share/doc/${PROJECT_NAME}
install(FILES main.c
    DESTINATION share/doc/${PROJECT_NAME}
)
# ... (Οι εντολές add_executable και install() παραμένουν ως έχουν)
# install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
# install(FILES LICENSE DESTINATION share/doc/${PROJECT_NAME})
# install(FILES main.c DESTINATION share/doc/${PROJECT_NAME})


# -----------------------------------------------
# ΛΟΓΙΚΗ ΑΠΕΓΚΑΤΑΣΤΑΣΗΣ (UNINSTALL)
# -----------------------------------------------

# 1. Ορίζουμε τον φάκελο όπου θα καταγραφεί η διαδικασία εγκατάστασης
set(CMAKE_INSTALL_INFODIR "${CMAKE_BINARY_DIR}/install_manifest")

# 2. Δημιουργούμε ένα custom target για την απεγκατάσταση
# Αυτό το target:
#   α) Διαβάζει το αρχείο install_manifest.txt (που δημιουργείται κατά το make install)
#   β) Διαγράφει κάθε αρχείο που περιέχεται σε αυτό το manifest
add_custom_target(uninstall
    # Χρησιμοποιεί το CMake ως script
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_uninstall.cmake
    # Το κάνουμε να λειτουργεί πάντα, ανεξάρτητα από τις εξαρτήσεις
    VERBATIM
)

# 3. Δημιουργούμε το script απεγκατάστασης (cmake_uninstall.cmake)
# Αυτό το script δημιουργείται δυναμικά από το CMake
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.in"
    "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
    @ONLY
)