#pragma once

#include <X11/Xutil.h>

#include "xpet.h"

#define PET_SPEED       2       /* pixels per frame - constant movement speed */
#define PET_REFRESH     24      /* ms between movement updates (16ms=60fps) */
#define FRAME_DURATION  200     /* ms between frames (can be overridden per frame) */
#define PET_ASSET_DIR   "./pets/neko"

#define PET_SPEED       20      /* pixels per frame - constant movement speed               */
#define PET_REFRESH     200     /* ms between movement updates (16ms=60fps)                 */
#define FRAME_DURATION  200     /* ms between frames (can be overridden per frame)          */
#define UNFREEZE_DELAY  2000    /* ms before pet walks again after unfreezing               */

#define WANDER_MIN_WAIT 16000   /* min ms to wait at destination                            */
#define WANDER_MAX_WAIT 32000   /* max ms to wait at destination                            */
#define WANDER_MARGIN   100     /* pixels from screen edge                                  */

#define SLEEP_DELAY     5000    /* ms frozen before falling asleep                          */
#define HAPPY_DURATION  3000    /* ms to stay happy after being clicked                     */
#define SPEECH_DURATION 3000    /* ms to show speech bubble                                 */

/* speech bubble sizing */
#define SPEECH_PAD_X    8
#define SPEECH_PAD_Y    6
#define SPEECH_MIN_W    24
#define SPEECH_MIN_H    16

/* speech phrases */
const char* pet_phrases[] = {
    // माया लाग्दो र मीठो
    "म्याऊ! माया गर, माया गर, अझै धेरै माया गर!", 
    "मुसुलाई तिमी सबभन्दा धेरै मन पर्छ, म्याऊ।", 
    "मुसु यहीँ सुत्छु है। न्यानो छ!", 
    "चुरु नदिए टोकिदिन्छु नि~!", 
    "मुसु! अँगालो हालूँ?", 
    "म्याऊ, म्याऊ, म तिर हेर त!", 
    "काँख उधारो लिएँ है!", 

    // आग्रहपूर्ण र चुलबुले
    "खाना! खाना! पेट खाली छ, म्याऊ।", 
    "खिलौना दिनुहोस्! खेल्न मन लाग्यो नि, म्याऊ!", 
    "अझै सुत्ने? उठ! उठ! म्याऊ!", 
    "मुसुलाई समातेर 'हाई-हाई' गर न!", 
    "सीरक अर्को एउटा चाहियो, म्याऊ।", 
    "माछाको सपना देखें नि, म्याऊ।", 

    // प्यारो र अल्लारे
    "'गुथा-गुथ' राम्रो गर्छु नि, होइन र?", 
    "बाकस, बाकस! यो मुसुको हो नि।", 
    "पुच्छर हल्लाउनु भनेको म खुसी छु भनेको नि।", 
    "मेरो पुठ्ठा प्यारो छ, म्याऊ?", 
    "माफ गर्नुहोस्, त्यो ग्लास खसालें मैले।", 
    "पल्टिएर सुतेँ! पेटमा माया गर्नुहोस् न, म्याऊ।", 

    // Short and Punchy (छोटो र दमदार)
    "म्याऊ-म्याऊ।", 
    "खाना आयो?", 
    "धेरै मन पर्छ!",
    "निन्द्रा लाग्यो...", 
    "के हो?",
    "च्याप।", 
    NULL  /* sentinel, do not remove */
};

struct bind bindings[] = {
	{.sym = XK_f, .mask = Mod1Mask | ShiftMask}, /* call/chase toggle */
	{.sym = XK_s, .mask = Mod1Mask | ShiftMask}, /* freeze toggle */
	{.sym = XK_q, .mask = Mod1Mask | ShiftMask}, /* quit */
};

struct animation animations[] = {
	[HAPPY]    = { .name = "happy",     .n_frames = 6, .loop = True, .frames = NULL, .frame_durations = NULL },
	[SLEEPING] = { .name = "sleeping",  .n_frames = 6, .loop = True, .frames = NULL, .frame_durations = NULL},
	[IDLE]     = { .name = "idle",      .n_frames = 6, .loop = True, .frames = NULL, .frame_durations = NULL },
	[DRAGGED]  = { .name = "dragged",   .n_frames = 6, .loop = True, .frames = NULL, .frame_durations = NULL },

	[N]  = { .name = "walk_north",      .n_frames = 2, .loop = True, .frames = NULL, .frame_durations = NULL },
	[S]  = { .name = "walk_south",      .n_frames = 2, .loop = True, .frames = NULL, .frame_durations = NULL },
	[E]  = { .name = "walk_east",       .n_frames = 2, .loop = True, .frames = NULL, .frame_durations = NULL },
	[W]  = { .name = "walk_west",       .n_frames = 2, .loop = True, .frames = NULL, .frame_durations = NULL },
	[NW] = { .name = "walk_northwest",  .n_frames = 2, .loop = True, .frames = NULL, .frame_durations = NULL },
	[NE] = { .name = "walk_northeast",  .n_frames = 2, .loop = True, .frames = NULL, .frame_durations = NULL },
	[SW] = { .name = "walk_southwest",  .n_frames = 2, .loop = True, .frames = NULL, .frame_durations = NULL },
	[SE] = { .name = "walk_southeast",  .n_frames = 2, .loop = True, .frames = NULL, .frame_durations = NULL },
};
