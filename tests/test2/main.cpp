//
// Copyright (c) 2018 Jamie Kenyon. All Rights Reserved.
//

#include <logService.hpp>

int main()
{
	wls::Service service("Test2");

	service.logInformation(42, "Hello Jamie.", 1.0f);

	return 0;
}
