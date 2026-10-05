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

$(OUTPUT_DIR)/TailLoops.c: KRML_FLAGS += -ftail-calls

.PHONY: check-tail-loops
all: check-tail-loops

$(OUTPUT_DIR)/TailLoops.exe: $(OUTPUT_DIR)/TailLoops.c TailLoops.test.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -std=c11 -Wall -Wextra -Werror \
		-I../../include -I../../krmllib/dist/minimal -I$(OUTPUT_DIR) $^ -o $@

check-tail-loops: $(OUTPUT_DIR)/TailLoops.exe
	$<
