#summary Typedefs, enums and data structures.
#labels Featured

= `exceptions4c` Types =

These are all the types defined in `exceptions4c`:

  * *[#e4c_exception_type e4c_exception_type]* represents an exception type in the exception handling system.
  * *[#e4c_exception e4c_exception]* represents an instance of an exception type.
  * *[#e4c_status e4c_status]* represents the completeness of a code block aware of exceptions.
  * *[#e4c_uncaught_handler e4c_uncaught_handler]* represents a function which will be executed in the event of an uncaught exception.
  * *[#e4c_signal_mapping e4c_signal_mapping]* represents a map between a signal and an exception.

----

= [http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/type.png] `e4c_exception_type` =

Represents an exception type in the exception handling system.

== Data Fields ==

  * *`name`*: The name of this exception type.
  * *`message`*: The default message of this exception type.
  * *`super`*: The supertype of this exception type.

== Detailed Description ==

The types of the exceptions a program will use are *defined* in source code files through the macro [macros#E4C_DEFINE_EXCEPTION E4C_DEFINE_EXCEPTION]. In addition, they are *declared* in header files through the macro [macros#E4C_DECLARE_EXCEPTION E4C_DECLARE_EXCEPTION].

When defining types of exceptions, they are given a _name_, a _default message_ and a _supertype_ to organize them into a _pseudo-hierarchy_:

{{{
E4C_DEFINE_EXCEPTION(SimpleException, "Simple exception", RuntimeException);
}}}

Exceptions are usually defined as global objects. There is a set of predefined exceptions built into the framework, and `RuntimeException` is the root of the exceptions _pseudo-hierarchy_:

  * `RuntimeException`
    * `NotEnoughMemoryException`
    * `IllegalArgumentException`
    * `FileOpenException`
    * `IllegalArgumentException`
    * `SignalException`
      * `SignalAlarmException`
      * `SignalChildException`
      * `SignalTrapException`
      * `ErrorSignalException`
        * `IllegalInstructionException`
        * `ArithmeticException`
        * `BrokenPipeException`
        * `BadPointerException`
          * `NullPointerException`
      * `ControlSignalException`
        * `StopException`
        * `KillException`
        * `HangUpException`
        * `TerminationException`
        * `AbortException`
        * `CPUTimeException`
        * `UserControlSignalException`
          * `UserQuitException`
          * `UserInterruptionException`
          * `UserBreakException`
      * `ProgramSignalException`
        * `ProgramSignal1Exception`
        * `ProgramSignal2Exception`

== See Also ==

  * *[#e4c_exception e4c_exception]*
  * *[macros#E4C_DEFINE_EXCEPTION E4C_DEFINE_EXCEPTION]*
  * *[macros#E4C_DECLARE_EXCEPTION E4C_DECLARE_EXCEPTION]*
  * *[keywords#throw throw]*
  * *[keywords#catch catch]*

----

= [http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/type.png] `e4c_exception` =

Represents an instance of an exception type.

== Data fields ==
  * *`name`*: The name of this exception.
  * *`message`*: The message of this exception.
  * *`file`*: The path of the source code file from which the exception was thrown.
  * *`line`*: The number of line from which the exception was thrown.
  * *`function`*: The function from which the exception was thrown.
  * *`error_number`*: The value of errno at the time the exception was thrown.
  * *`type`*: The type of this exception.
  * *`cause`*: The cause of this exception.

== Detailed Description ==

Exceptions are a means of breaking out of the normal flow of control of a code block in order to handle errors or other exceptional conditions. An exception should be thrown at the point where the error is detected; it may be handled by the surrounding code block or by any code block that directly or indirectly invoked the code block where the error occurred.

Exceptions provide information regarding the exceptional situation, such as:

  * The exception _name_ and _type_
  * An _ad-hoc_ message (as opposed to the _default_ one)
  * The exact point of the program where it was thrown (source code _file_, _line_ and _function name_, if available)
  * The value of the standard error code `errno` at the time the exception was thrown
  * The `cause` of the exception, which is the previous exception (if any), when the exception was thrown from a `catch` or `finally` block
  * The specific, _run-time_ type of the exception, convenient when handling an abstract type of exceptions in a `catch` block

`Note`: `Any` exception can be caught by a block introduced by `catch(RuntimeException)`, except for `AssertionException`.

== See Also ==

  * *[#e4c_exception_type e4c_exception_type]*
  * *[keywords#throw throw]*
  * *[keywords#catch catch]*
  * *[functions#e4c_get_exception e4c_get_exception]*
  * *[exceptions#RuntimeException RuntimeException]*
  * *[exceptions#AssertionException AssertionException]*

----

= [http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/type.png] `e4c_status` =

Represents the completeness of a code block aware of exceptions:

== Values ==

  * *`e4c_succeeded`* There were no exceptions.
  * *`e4c_recovered`* There was an exception, but it was caught.
  * *`e4c_failed`* There was an exception and it wasn't caught.

== Detailed Description ==

The symbolic values representing the status of a block help to distinguish between different possible situations inside a finally block. For example, different cleanup actions can be taken, depending on the status of the block.

{{{
try{
    ...
}finally{
    switch( e4c_get_status() ){

        case e4c_succeeded:
            ...
            break;

        case e4c_recovered:
            ...
            break;

        case e4c_failed:
            ...
            break;
    }
}
}}}

== See Also ==

  * *[functions#e4c_get_status e4c_get_status]*
  * *[keywords#finally finally]*

----

= [http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/type.png] `e4c_uncaught_handler` =

Represents a function which will be executed in the event of an uncaught exception.

== Parameters ==

  * *`exception`* The uncaught exception

== Detailed Description ==

These functions are specified when a new exception context is begun:

{{{
void my_uncaught_handler(const e4c_exception * exception){

    printf("Error: %s (%s)\n", exception->name, exception->message);
}

...

int main(int argc, char * argv[]){

    e4c_using_context(E4C_TRUE){

        e4c_context_set_handlers(my_uncaught_handler, NULL, NULL, NULL);
        /* ... */
    }
}

}}}

There exists a convenience function `#e4c_print_exception` which is used as the default *uncaught handler*, unless otherwise specified. It simply prints information regarding the exception to `stderr`.

*Warning*: These functions are not allowed to try and recover the current exception context. Moreover, the program (or current thread) will terminate right after the function returns.


== See Also ==

  * *[functions#e4c_context_begin e4c_context_begin]*
  * *[macros#e4c_using_context e4c_using_context]*
  * *[functions#e4c_print_exception e4c_print_exception]*

----

= [http://exceptions4c.googlecode.com/svn/trunk/etc/img/icons/40x40/type.png] `e4c_signal_mapping` =

Represents a map between a signal and an exception.

== Data fields ==
  * *`signal_number`*: The signal to be converted.
  * *`exception_type`*: The exception representing the signal.

== Detailed Description ==

A signal is an asynchronous notification sent by the operating system to a process in order to notify it of an event that occurred. Most of the signals will, by default, crash the program as soon as they are raised. `exceptions4c` can convert signals to exceptions, so they can be easily handled.

For example, a _suspicious_ or _dangerous_ part of the program could be wrapped up with `try` blocks and then `catch` segmentation faults or divisions by zero. Then the program would clean up and continue normally:

{{{
e4c_using_context(E4C_TRUE){

    int * pointer = NULL;

    try{
        int oops = *pointer;
    }catch(BadPointerException){
        printf("No problem ;-)");
    }finally{
        // clean up...
    }
}
}}}

In order to perform the conversion, `exceptions4c` _maps_ signals to exceptions.

The simplest way to get this working is by calling the function `e4c_context_begin`. This function will set up the default mappings for the available signals in the platform, when passed `handle_signals=E4C_TRUE`.

If you need to be more specific about which signals get converted to exceptions, you can define an array of signal mappings:

{{{
const e4c_signal_mapping my_signal_mappings[] = {
    E4C_SIGNAL_MAPPING(SIGABRT, Exception1),
    E4C_SIGNAL_MAPPING(SIGINT, Exception2),
    E4C_IGNORE_SIGNAL(SIGTERM),
    ...
    E4C_NULL_SIGNAL_MAPPING
}
}}}

An array of signal mappings is defined through the macros `E4C_SIGNAL_MAPPING`, `E4C_IGNORE_SIGNAL` and `E4C_NULL_SIGNAL_MAPPING`. Every `e4c_signal_mapping` array needs to be terminated by the _null signal mapping_ element, so the system finds out how many mappings there are in a given array.

Once the array is properly defined, it can be passed to the function `e4c_context_set_signal_mappings`. This way, only the specified signals will be handled as exceptions, and they will be converted to the specified exceptions.

{{{
e4c_using_context(E4C_FALSE){

    e4c_context_set_signal_mappings(my_signal_mappings);
    // ...
}
}}}

Additionally, you can _ignore_ specific signals by using `E4C_IGNORE_SIGNAL` instead of `E4C_SIGNAL_MAPPING`. If the specified signal is raised, the system won't convert it to an exception and the program will continue (even if unmeaningful).

These are some of the signals you can handle:

  * *`SIGFPE`* when dividing by zero.
  * *`SIGSEGV`* when dereferencing an invalid pointer.
  * *`SIGINT`* when a user interrupts the process.
  * *`SIGTERM`* when a process is requested to be terminated.

== See Also ==

  * *[functions#e4c_context_begin e4c_context_begin]*
  * *[functions#e4c_context_set_signal_mappings e4c_context_set_signal_mappings]*
  * *[functions#e4c_context_get_signal_mappings e4c_context_get_signal_mappings]*
  * *[macros#E4C_SIGNAL_MAPPING E4C_SIGNAL_MAPPING]*
  * *[macros#E4C_IGNORE_SIGNAL E4C_IGNORE_SIGNAL]*
  * *[variables#e4c_default_signal_mappings e4c_default_signal_mappings]*

----

[http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png]