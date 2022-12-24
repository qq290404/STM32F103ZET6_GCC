TOP := .

sinclude $(TOP)/.config
include $(TOP)/Makefile.build
include $(TOP)/Makefile.func

MENUCONFIG_UTIL := $(PYTHON) $(TOP)/tools/kconfiglib/menuconfig.py
GENCONFIG_UTIL  := $(PYTHON) $(TOP)/tools/kconfiglib/genconfig.py
# style: aquatic, default, monochrome
MENUCONFIG_STYLE:="monochrome selection=fg:black,bg:yellow"

DIRS += preinit
DIRS += app

.PHONY: rebuild all clean $(DIRS)
.PHONY: menuconfig

all:
	@$(call FOREACH_EXECUTE_FUNC,$(DIRS),$@)

clean:
	@$(call FOREACH_EXECUTE_FUNC,$(DIRS),$@)
	@$(RM) -rf $(TOP)/out

rebuild:
	@$(MAKE) clean --no-print-directory
	@$(MAKE) all --no-print-directory

menuconfig:
	@MENUCONFIG_STYLE=$(MENUCONFIG_STYLE) srctree=$(TOP) KCONFIG_CONFIG=.config $(MENUCONFIG_UTIL) Kconfig

genconfig:
	@srctree=$(TOP)/sdk $(GENCONFIG_UTIL)

include $(TOP)/Makefile.tools
