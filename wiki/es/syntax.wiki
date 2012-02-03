#summary Sintaxis

= Un poco de `contexto` =

El código del programa que está al tanto del sistema de excepciones tiene que encuadrarse dentro de un *contexto*. Un contexto tiene que ser _iniciado_ antes de usar el manejo de excepciones y _terminado_ antes de salir de la aplicación o hilo de ejecución.

La forma más fácil de hacer esto es a través de la _macro_ `e4c_using_context`. Todo lo que haya dentro de este bloque de código (o funciones llamadas desde este bloque de código) tiene un contexto listo para ser usado. Por ejemplo, puedes ponerlo en la función `main` y ya está:

{{{
int main(int argc, char * argv[]){
    e4c_using_context(true, e4c_print_exception){
        ...
    }
}
}}}

Hay otra forma de iniciar y terminar un contexto, a través de las funciones `e4c_context_begin` y `e4c_context_end`, pero hay que usarlas _correctamente_ (no se puede llamar dos veces seguidas a ninguna de estas funciones y además hay que terminar el contexto antes de salir).

= Tipos de excepciones =

Los tipos de excepciones que un programa puede usar se definen dentro del ámbito global de un archivo de código fuente con la _macro_ `E4C_DEFINE_EXCEPTION` especificando: *nombre*, *mensaje de error por defecto* y *supertipo*:

{{{
/* stack.c */
...
E4C_DEFINE_EXCEPTION(StackException, "Stack overflow", RuntimeException);
E4C_DEFINE_EXCEPTION(StackOverflowException, "Stack overflow", StackException);
E4C_DEFINE_EXCEPTION(StackUnderflowException, "Stack underflow", StackException);
...
}}}

Se pueden declarar en un archivo de cabecera con la _macro_ `E4C_DECLARE_EXCEPTION`:

{{{
/* stack.h */
...
E4C_DECLARE_EXCEPTION(StackException);
E4C_DECLARE_EXCEPTION(StackOverflowException);
E4C_DECLARE_EXCEPTION(StackUnderflowException);
...
}}}

= `throw` =

La _palabra clave_ `throw` crea una nueva instancia del tipo de excepción especificado, con un mensaje especificado y la lanza para señalar una situación excepcional al sistema.

Si el mensaje especificado es `NULL` se usará el mensaje por defecto para ese tipo de excepción.

{{{
if(record == null) throw(NullPointerException, "Invalid record passed as parameter.");

buffer = malloc(1024);

if(buffer != null){
	...
}else{
	throw(NotEnoughMemoryException, NULL);
}
}}}

Las excepciones se pueden lanzar en cualquier momento, siempre que haya un contexto listo para ser usado. También pueden ser lanzadas desde bloques `catch` y `finally`.

= `try` =

La única parte obligatoria de un bloque `try` es la _palabra clave_ `try`. Un bloque de código introducido por la palabra clave `try` puede usar bloques `catch` para manejar errores, y un bloque `finally` para la _limpieza_ después de ejecutarse el bloque `try`, tanto en caso de _éxito_ como de _fracaso_.

{{{
try{
    stack_push(123);
}
}}}

= `catch` =

A un bloque `catch` hay que darle el tipo de excepciones que es capaz de manejar. Dentro de un bloque `catch` se puede acceder a la excepción que se está manejado concretamente, a través de la función `e4c_get_exception`.

{{{
try{
    stack_push(123);
}catch(StackException){
    printf("Last operation failed (%s).\n", e4c_get_exception()->message);
}
}}}

Un bloque `try` puede ir acompañado de muchos bloques `catch`:

{{{
try{
    stack_push(stack, 123);
    foo = stack_pop(stack);
}catch(StackOverflowException){
    /* ... */
}catch(StackUnderflowException){
    /* ... */
}
}}}

= `finally` =

Un bloque `try` puede ir seguido de, como mucho, un bloque `finally`. Para averiguar si el bloque `try` se completó o lanzó una excepción, se puede llamar a la función `e4c_get_status`. La función `e4c_get_exception` devolverá la excepción que se lanzó, si existe, incluso si se capturó por un bloque `catch`.

{{{
try{
    stack_push(123);
}finally{
    fclose(file);
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

----

[http://exceptions4c.googlecode.com/svn/trunk/etc/img/logo/exceptions4c_128.png]