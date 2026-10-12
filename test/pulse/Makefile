include test.mk

# Some tests have extra dependencies.
$(OUTPUT_DIR)/Example_Hashtable.c: $(addprefix $(OUTPUT_DIR)/,\
	FStar_Pervasives.krml \
	FStar_Pervasives_Native.krml \
	Pulse_Lib_Vec.krml \
	Pulse_Lib_HashTable_Type.krml \
	Pulse_Lib_HashTable_Spec.krml \
	Pulse_Lib_HashTable.krml)

$(OUTPUT_DIR)/Example_Slice.c: $(addprefix $(OUTPUT_DIR)/,\
	Pulse_Lib_Slice.krml)

$(OUTPUT_DIR)/Example_Unreachable.c: $(addprefix $(OUTPUT_DIR)/,\
	FStar_Pervasives.krml \
	FStar_Pervasives_Native.krml)

# Inline enough so the augmented assignments actually kick in
$(OUTPUT_DIR)/CompoundAssignment.c: KRML_FLAGS += -faggressive-inlining

$(OUTPUT_DIR)/PassByReference.c: KRML_FLAGS += -fnostruct-passing

# Inlining exposes reads through aliases in the replacement and destination.
# Fail if a malformed transformed function would otherwise be dropped.
$(OUTPUT_DIR)/FunctionalUpdates.c: KRML_FLAGS += -faggressive-inlining -warn-error @4

$(OUTPUT_DIR)/FunctionalUpdates.exe: $(OUTPUT_DIR)/FunctionalUpdates.c FunctionalUpdates.main.c
	$(call msg, "CC", $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -I$(OUTPUT_DIR) -I../../include -I../../krmllib/dist/minimal $^ $(LDFLAGS) -o $@

.PHONY: functional-updates
functional-updates: $(OUTPUT_DIR)/FunctionalUpdates.exe
	$(call msg, "RUN", $<)
	$<

all: functional-updates
