
typedef enum td_keycodes_t {
    TD_LGUI,
    TD_APP,
    TD_PGUP,
    TD_PGDN,
    TD_RSHIFT,
    TD_LSHIFT,
    TD_RCTRL,
    TD_LCTRL,
} td_keycodes_t;

typedef enum td_state_t {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(qk_tap_dance_state_t *state);

void TD_APP_FINISHED(qk_tap_dance_state_t *state, void *user_data);
void TD_APP_RESET(qk_tap_dance_state_t *state, void *user_data);

void TD_RSHIFT_FINISHED(qk_tap_dance_state_t *state, void *user_data);
void TD_RSHIFT_RESET(qk_tap_dance_state_t *state, void *user_data);

void TD_LSHIFT_FINISHED(qk_tap_dance_state_t *state, void *user_data);
void TD_LSHIFT_RESET(qk_tap_dance_state_t *state, void *user_data);

void TD_LCTRL_FINISHED(qk_tap_dance_state_t *state, void *user_data);
void TD_LCTRL_RESET(qk_tap_dance_state_t *state, void *user_data);
