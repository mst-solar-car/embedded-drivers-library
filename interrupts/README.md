# Interrupts
This driver handles registration of interrupts and generic dispatching of interrupts.

The following functions are available to the user:

| Syntax | Description |
|----------|-------------|
|`void interrupts_enable()` | Turns on interrupts (probably done by default) |
|`void interrupts_disable()`| Turns off interrupts |
|`void interrupt_attach(pin, func)`|Registers `func` to execute when there is an interrupt on `pin`|


&nbsp;

# Alternative Syntax
There is an alternative syntax to `interrupt_attach`, please see the [interrupts example](../EXAMPLES.md#interrupts) for more information.