#include "CppUnitTest.h"

#include <Utilities/ResourceLoader.h>
#include <TestHelpers/TestDefaultLoggerHelper.h>
#include <TestHelpers/TestFilesystemHelpers.h>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
	TEST_CLASS(SFResourceLoaderTests)
	{
	public:
		TEST_METHOD_CLEANUP(TestCleanup)
		{
			TestHelpers::CleanupDefaultLoggerForTests();
		}
	};
}