# Bits Utility
The bits utility can be used to perform operations on bits and bytes.

# Functions

| Syntax | Description |
|--------|-------------|
|`bits_set_high(value, bits)` | Sets the `bits` high inside of `value`. |
|`bits_set_low(value, bits)` | Sets the `bits` low inside of `value`. |
|`bits_toggle(value, bits)` | Flips `bits` inside of `value`. |
|`bits_get(value, bits)` | Returns the state of `bits` inside of `value`. |
|&nbsp;|&nbsp;|
|`bits_is_high(value, bits)` | Evaluates to `True` if `bits` are all set high in `value`. |
|`bits_is_low(value, bits)` | Evaluates to `True` if `bits` are all set low in `value`. |
| &nbsp; |&nbsp;|
|`bits_left_shift(value, n)` | Shifts `value` to the left `n` times. |
|`bits_right_shift(value, n)` | Shifts `value` to the right `n` times. |