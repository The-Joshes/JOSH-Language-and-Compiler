all= html

DOXYGEN_DIR = doxygen/
DOXYGEN = doxygen
DOXYFILE = Doxyfile
HOME_DIR = ..

.PHONY: doxygen

doxygen: 
	cd $(DOXYGEN_DIR) && $(DOXYGEN) $(DOXYFILE) && cd $(HOME_DIR)

clean: 
	cd $(DOXYGEN_DIR) && rm html/ latex/ -rf && cd $(HOME_DIR)
