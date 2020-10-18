# Makefile to build class 'vas_binaural' for Pure Data.
# Needs Makefile.pdlibbuilder as helper makefile for platform-dependent build
# settings and rules.

# library name

# add folder shortcut examples:
# INCLUDES = -I../includes
# TESTING = testing

lib.name = ph_formant_osc

# input source file (class name == source file basename)
class.sources = ph_formant_osc~.c

ph_formant_osc~.class.sources  = vas_mem.c
ph_formant_osc~.class.sources += vas_osc.c

# all extra files to be included in binary distribution of the library
datafiles =

# include Makefile.pdlibbuilder from submodule directory 'pd-lib-builder'
PDLIBBUILDER_DIR=../pd-lib-builder/

CC += $(INCLUDES)
# CC +=  -mavx -DVAS_USE_AVX

include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder