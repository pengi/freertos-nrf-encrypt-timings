include make/once.mk

OBJ_DIR=build/obj-$(APP)
GEN_DIR=$(OBJ_DIR)

include make/targets/$(APP).mk
include make/verbosity.mk

rp = $(shell realpath --relative-to . $1)

SRC_FILES = $(SRC) $(foreach mod,$(MODULES),$(wildcard $(mod)/*.c))
OBJS = \
	$(patsubst %.S,$(OBJ_DIR)/%.o, \
	$(patsubst %.c,$(OBJ_DIR)/%.o, \
		$(SRC_FILES) \
	)) \
	$(addprefix $(OBJ_DIR)/,$(GEN_OBJS))
INC_FLAGS = $(addprefix -I,$(INC) $(MODULES))

default: $(TARGETDIR)$(APP)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(TRACE) "CC" $<
	$Q$(CC) -c -o $@ $(CFLAGS) $(INC_FLAGS) $<
	
$(OBJ_DIR)/%.o: $(GEN_DIR)/%.c
	@mkdir -p $(@D)
	$(TRACE) "CC" $<
	$Q$(CC) -c -o $@ $(CFLAGS) $(INC_FLAGS) $<

$(OBJ_DIR)/%.o: %.S
	@mkdir -p $(@D)
	$(TRACE) "CC" $<
	$Q$(CC) -c -o $@ $(CFLAGS) $(INC_FLAGS) $<

$(OBJ_DIR)/%.o: $(GEN_DIR)/%.c
	@mkdir -p $(@D)
	$(TRACE) "CC" $<
	$Q$(CC) -c -o $@ $(CFLAGS) $(INC_FLAGS) $<

$(TARGETDIR)$(APP): $(OBJS) $(LIBS)
	@mkdir -p $(@D)
	$(TRACE) "LD" $@
	$Q$(LD) -o $@ $(LDFLAGS) $^

%.hex: %.elf
	@mkdir -p $(@D)
	$(TRACE) "OBJCOPY" $@
	$Q$(OBJCOPY) -O ihex $^ $@

# Dependency tracking, together with -MMD
-include $(patsubst %.o,%.d,$(filter %.o,$(OBJS)))

FORCE:

.PHONY: FORCE