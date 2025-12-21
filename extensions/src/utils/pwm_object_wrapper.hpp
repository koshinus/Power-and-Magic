#pragma once

#include <string>

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/object.hpp>

namespace pwm
{

struct TestObjInfo: public godot::Object
//class TestObjInfo: public godot::Node
{
    //GDCLASS( TestObjInfo, godot::Node )
public:
    TestObjInfo() : godot::Object() {}
    TestObjInfo( std::string s ) : godot::Object() { m_line = s; }
    /*
    TestObjInfo& operator=( const TestObjInfo& other )
    {
        return *this;
    }
    */
    ~TestObjInfo() {}
    std::string m_line;
protected:
    //static void _bind_methods() {}
};

}

/*
template <>
struct godot::GetTypeInfo<pwm::TestObjInfo> {
    static constexpr GDExtensionVariantType VARIANT_TYPE = GDEXTENSION_VARIANT_TYPE_OBJECT;
    static constexpr GDExtensionClassMethodArgumentMetadata METADATA = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE;
    static inline PropertyInfo get_class_info() {
        return make_property_info(Variant::Type::OBJECT, "", PROPERTY_HINT_RESOURCE_TYPE, pwm::TestObjInfo::get_class_static());
    }
};

template <>
struct godot::PtrToArg<pwm::TestObjInfo> {
    _FORCE_INLINE_ static pwm::TestObjInfo convert(const void *p_ptr) {
        return *reinterpret_cast<const pwm::TestObjInfo *>(p_ptr);
    }

    using EncodeT = pwm::TestObjInfo;

    _FORCE_INLINE_ static void encode(pwm::TestObjInfo p_val, void *p_ptr) {
        *reinterpret_cast<pwm::TestObjInfo *>(p_ptr) = p_val;
    }
}; 
*/
