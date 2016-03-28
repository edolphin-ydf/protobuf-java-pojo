
#include "java_pojo_plugin.h"
#include <google/protobuf/compiler/plugin.h>
#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/stubs/shared_ptr.h>
#include <stdio.h>
#include <list>

PojoGeneratorHelper::JavaType PojoGeneratorHelper::GetJavaType(const FieldDescriptor* field) {
	switch (field->type()) {
		case FieldDescriptor::TYPE_INT32:
		case FieldDescriptor::TYPE_UINT32:
		case FieldDescriptor::TYPE_SINT32:
		case FieldDescriptor::TYPE_FIXED32:
		case FieldDescriptor::TYPE_SFIXED32:
			return JAVATYPE_INT;

		case FieldDescriptor::TYPE_INT64:
		case FieldDescriptor::TYPE_UINT64:
		case FieldDescriptor::TYPE_SINT64:
		case FieldDescriptor::TYPE_FIXED64:
		case FieldDescriptor::TYPE_SFIXED64:
			return JAVATYPE_LONG;

		case FieldDescriptor::TYPE_FLOAT:
			return JAVATYPE_FLOAT;

		case FieldDescriptor::TYPE_DOUBLE:
			return JAVATYPE_DOUBLE;

		case FieldDescriptor::TYPE_BOOL:
			return JAVATYPE_BOOLEAN;

		case FieldDescriptor::TYPE_STRING:
			return JAVATYPE_STRING;

		case FieldDescriptor::TYPE_BYTES:
			return JAVATYPE_BYTES;

		case FieldDescriptor::TYPE_ENUM:
			return JAVATYPE_ENUM;

		case FieldDescriptor::TYPE_GROUP:
		case FieldDescriptor::TYPE_MESSAGE:
			return JAVATYPE_MESSAGE;

			// No default because we want the compiler to complain if any new
			// types are added.
	}

	GOOGLE_LOG(FATAL) << "Can't get here.";
	return JAVATYPE_INT;
}

const char* PojoGeneratorHelper::PrimitiveTypeName(JavaType type) {
	switch (type) {
		case JAVATYPE_INT    : return "int";
		case JAVATYPE_LONG   : return "long";
		case JAVATYPE_FLOAT  : return "float";
		case JAVATYPE_DOUBLE : return "double";
		case JAVATYPE_BOOLEAN: return "boolean";
		case JAVATYPE_STRING : return "java.lang.String";
		case JAVATYPE_BYTES  : return "com.google.protobuf.ByteString";
		case JAVATYPE_ENUM   : return NULL;
		case JAVATYPE_MESSAGE: return NULL;

							   // No default because we want the compiler to complain if any new
							   // JavaTypes are added.
	}

	GOOGLE_LOG(FATAL) << "Can't get here.";
	return NULL;
}

const string PojoGeneratorHelper::determinType(const FieldDescriptor* field) {
	const char* type = PrimitiveTypeName(GetJavaType(field));
	if (type == NULL) {
		switch(field->type()) {
			case FieldDescriptor::TYPE_ENUM:
				type = field->enum_type()->name().c_str();
				break;
			case FieldDescriptor::TYPE_MESSAGE:
				type = field->message_type()->name().c_str();
				break;
			default:
				break;
		}
	}
	return string(type);
}


bool PojoGenerator::Generate(const google::protobuf::FileDescriptor* file,
		const string& parameter,
		compiler::GeneratorContext* generator_context,
		std::__cxx11::string* error) const {

	const FileOptions& fileOptions = file->options();
	string javaOuterClassName = fileOptions.java_outer_classname();
	io::ZeroCopyOutputStream* outFile = generator_context->Open(javaOuterClassName + ".pojo.java");
	scoped_ptr<io::ZeroCopyOutputStream> scoped_output(outFile);

	io::Printer printer(outFile, '$');

	printer.Print("public class $outerClassName$ {\n", "outerClassName", javaOuterClassName);

	for (int i = 0; i < file->enum_type_count(); i++) {
		const EnumDescriptor *enumDesc = file->enum_type(i);
		printer.Print("\tenum $enumName$ {\n", "enumName", enumDesc->name());
		for (int j=0; j<enumDesc->value_count(); ++j) {
			const EnumValueDescriptor *evdesc = enumDesc->value(j);
			printer.Print("\t\t$value$,\n", "value", evdesc->name());
		}
		printer.Print("\t}\n\n");
	}

	for (int i = 0; i < file->message_type_count(); i++) {
		const Descriptor *msgDesc = file->message_type(i);
		printer.Print("\tpublic static class $msgClassName$ {\n", "msgClassName", msgDesc->name());
		for (int j = 0; j < msgDesc->field_count(); j++) {
			const FieldDescriptor *fieldDesc = msgDesc->field(j);
			printer.Print("\t\tprivate $fieldType$ $fieldName$;\n", 
					"fieldType", PojoGeneratorHelper::determinType(fieldDesc), 
					"fieldName", fieldDesc->camelcase_name());
		}

		for (int j = 0; j < msgDesc->field_count(); j++) {
			const FieldDescriptor *fieldDesc = msgDesc->field(j);
			string type = PojoGeneratorHelper::determinType(fieldDesc);

			string funcName(fieldDesc->camelcase_name());
			if (funcName[0] >='a' && funcName[0] <= 'z')
				funcName[0] = funcName[0] + ('A' - 'a');

			printer.Print("\t\tpublic void set$name$($type$ $paramName$) { this.$paramName$=$paramName$; }\n", 
					"type", type, 
					"name", funcName, 
					"paramName", fieldDesc->camelcase_name());
			printer.Print("\t\tpublic $type$ get$name$() { return this.$paramName$; }\n", 
					"type", type, 
					"name", funcName, 
					"paramName", fieldDesc->camelcase_name());
		}
		printer.Print("\t}\n\n");
	}
	printer.Print("}\n");
	return true;
}


int main(int argc, char* argv[]) {
	//printf("in plugin\n");
	PojoGenerator  pojoGenerator;
	return PluginMain(argc, argv, &pojoGenerator);
}



