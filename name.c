// This file allows to specify a custom name for the MIDI device.
// It must be kept at name.c under the root folder.

#include "usb_names.h"

// Edit these lines to create your own name.  The length must
// match the number of characters in your custom name.

#define MIDI_NAME   {'J','u','s','t',' ','B','e','t','w','e','e','n',' ','U','s'}
#define MIDI_NAME_LEN  15

// Do not change this part.  This exact format is required by USB.

struct usb_string_descriptor_struct usb_string_product_name = {
        2 + MIDI_NAME_LEN * 2,
        3,
        MIDI_NAME
};
