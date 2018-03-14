# Pin Control
The pin control driver is used for generic pin control for microcontrollers.

&nbsp;

# Functions
The following functions are exposed to the user via the pin control drivers:

| Syntax | Description |
|--------|-------------|
|`pin_set_mode(pin, mode)` | Configures `pin` into a certain `mode`. |
|`pin_set_level(pin, level)` | Sets `pin` output to `level`. |
|`pin_toggle(pin)` | Will set `pin` output to opposite of what it currently is. |
|`pin_level pin_read(pin)` | Will return the input level of `pin`. |