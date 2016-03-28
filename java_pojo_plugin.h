
#include <google/protobuf/compiler/code_generator.h>

namespace google{
namespace protobuf{
	class FieldDescriptor;
}
}

using namespace google::protobuf;
using namespace std;

class PojoGeneratorHelper {
public:
	enum JavaType {
		JAVATYPE_INT,
		JAVATYPE_LONG,
		JAVATYPE_FLOAT,
		JAVATYPE_DOUBLE,
		JAVATYPE_BOOLEAN,
		JAVATYPE_STRING,
		JAVATYPE_BYTES,
		JAVATYPE_ENUM,
		JAVATYPE_MESSAGE
	};

	static JavaType GetJavaType(const FieldDescriptor* field);
	static const char* PrimitiveTypeName(JavaType type);
	static const string determinType(const FieldDescriptor* field);
};

class PojoGenerator : public compiler::CodeGenerator {
public:
	PojoGenerator(){}

	virtual ~PojoGenerator() {}

	virtual bool Generate(const google::protobuf::FileDescriptor* file,
			const string& parameter,
			compiler::GeneratorContext* generator_context,
			std::__cxx11::string* error) const;
};


