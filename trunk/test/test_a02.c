
# include "testing.h"


DEFINE_TEST(
	a02,
	"throw(...) without beginning",
	"This test uses the library improperly, by attempting to <strong>throw an exception</strong>, without calling <code>e4c_context_begin()</code> first. The library must signal the misuse by throwing the exception <code>ContextHasNotBegunYet</code>.",
	NULL,
	EXIT_FAILURE,
	"before_THROW",
	"ContextHasNotBegunYet"
){

	printf("before_THROW\n");

	E4C_THROW(NullPointerException, "Actually, I can't throw an exception yet.");

	printf("after_THROW\n");

	return(EXIT_SUCCESS);
}

