#include <YSI_Core\y_testing>
#include "indirection"

new gCall = 0;

forward TestCallback3(a, arr[], size);

stock TestCallbackX(n, ...)
{
	ASSERT(numargs() == n + 1);
	gCall = 100;
}

stock TestCallbackV()
{
	ASSERT(numargs() == 0);
	gCall = 101;
}
#define CALL@TestCallbackV TestCallbackV()

static TestCallback0(a, b, c)
{
	ASSERT(numargs() == 3);
	gCall = a * b * c;
}

static TestCallback1(a, b, c)
{
	ASSERT(numargs() == 3);
	gCall = a + b + c;
}

static stock TestCallback2(a, string:s[], d)
{
	ASSERT(numargs() == 3);
	ASSERT(strcmp(s, "Hello World") == 0);
	ASSERT(s[0] != '\0');
	gCall = a * d;
}
#define CALL@TestCallback2 TestCallback2(0,"",0)

static TestCallback4(a, &b, c)
{
	ASSERT(numargs() == 3);
	gCall = a + b + c;
	--b;
}

public TestCallback3(a, arr[], size)
{
	ASSERT(numargs() == 3);
	ASSERT(a == size);
	gCall = arr[0] + arr[1];
}

TestCall1(Func:func<iii>, a, b, c)
{
	@.func(a, b, c);
}
#define TestCall1(&%0,%1) TestCall1(addressof(%0<iii>),%1)

TestCallArray1(Func:func<iii>, a, b, c)
{
	new
		arr[3];
	arr[0] = ref(a);
	arr[1] = ref(b);
	arr[2] = ref(c);
	Indirect_Array(_:func, tagof (func), arr);
}
#define TestCallArray1(&%0,%1) TestCallArray1(addressof(%0<iii>),%1)

TestCallArray2(Func:func<ivi>, a, &b, c)
{
	new
		arr[3];
	arr[0] = ref(a);
	arr[1] = ref(b);
	arr[2] = ref(c);
	Indirect_Array(_:func, tagof (func), arr);
}
#define TestCallArray2(&%0,%1) TestCallArray2(addressof(%0<ivi>),%1)

TestCall2(Func:func<isi>, a, d)
{
	@.func(a, "Hello World", d);
}

TestCall3(Func:func<iai>, a, arr[], size)
{
	@.func(a, arr, size);
}

Test:Indirect1()
{
	gCall = 0;
	TestCall1(&TestCallback0, 4, 5, 6);
	ASSERT(gCall == 120);
	gCall = 0;
	TestCall1(&TestCallback1, 4, 5, 6);
	ASSERT(gCall == 15);
}

Test:Indirect2()
{
	gCall = 0;
	TestCall2(Func:addressof(TestCallback2)<isi>, 99, 100);
	ASSERT(gCall == 9900);
}

Test:Indirect3()
{
	new arr[4] = { 5, 55, 555, 5555 };
	gCall = 0;
	TestCall3(Func:Indirect_Ref("TestCallback3")<iai>, 4, arr, sizeof (arr));
	ASSERT(gCall == 60);
}

Test:IndirectX()
{
	@&TestCallbackX<ix>(10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
}

Test:IndirectV()
{
	@&TestCallbackV();
	ASSERT(TRUE);
}

Test:IndirectArray()
{
	TestCallArray1(&TestCallback1, 9, 9, 9);
	ASSERT(gCall == 27);
	new
		a = 8;
	TestCallArray2(&TestCallback4, 9, a, 7);
	ASSERT(gCall == 24);
	ASSERT(a == 7);
	TestCallArray2(&TestCallback4, 9, a, 7);
	ASSERT(gCall == 23);
	ASSERT(a == 6);
	TestCallArray2(&TestCallback4, 9, a, 7);
	ASSERT(gCall == 22);
	ASSERT(a == 5);
}

TestCompile:Indirection()
{
	Indirect_Call(0, 0);
	Indirect_Array(0, 0, "", 0);
	Indirect_Callstring(0, 0);
	Indirect_Callvoid(0, 0);
	Indirect_Claim(0);
	Indirect_Release(0);
	Indirect_Tag(0, "");
	new
		Func:a<iii> = addressof (TestCallback1<iii>);
	@.a(0, 0, 0);
	@&TestCallback1<iii>(0, 0, 0);
}

