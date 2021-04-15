#include "common.h"

struct iso8859_15 {
        char code;
        char *html;
} he[] = {
        { 0xE4, "&auml;" },
        { 0xC4, "&Auml;" },
        { 0xF6, "&ouml;" },
        { 0xD6, "&Ouml;" },
        { 0xFC, "&uuml;" },
        { 0xDC, "&Uuml;" },
        { 0xDF, "&szlig;" },
        { 0xA4, "&euro;" },
        { 0x3C, "&lt;"  },
        { 0x3E, "&gt;"  },
        { 0x26, "&amp;" },
        { 0x22, "&quot;"}
};
