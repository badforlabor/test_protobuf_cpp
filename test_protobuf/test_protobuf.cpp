// test_protobuf.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "proto/example.pb.h"
using namespace google::protobuf;

Message* createMessage(const std::string& typeName)
{
	Message* message = NULL;
	const Descriptor* descriptor = DescriptorPool::generated_pool()->FindMessageTypeByName(typeName);
	if (descriptor)
	{
		const Message* prototype = MessageFactory::generated_factory()->GetPrototype(descriptor);
		if (prototype)
		{
			message = prototype->New();
		}
	}
	return message;
}

int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	exampleproto::LoginRequest msg;

	msg.set_account("1");
	msg.set_password("2");

	int size = msg.ByteSize();
	char* data = new char[size];
	msg.SerializeToArray(data, size);
	std::string type_name = exampleproto::LoginRequest::descriptor()->full_name();
	
	// 动态创建
	// http://www.voidcn.com/article/p-yhrtszie-rz.html
	auto one = createMessage(type_name);
	one->ParseFromArray(data, size);
	std::cout << one->GetTypeName() << std::endl;
	auto oneMsg = static_cast<exampleproto::LoginRequest*>(one);
	std::cout << oneMsg->account() << ":" << oneMsg->password() << std::endl;
	delete one;

	delete data;

    std::cout << "Hello World!\n"; 
	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
