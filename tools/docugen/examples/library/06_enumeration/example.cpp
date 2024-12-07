#include <omnilib>

OMNI_ENUM(easy_enum, NONE, VALUE_1, VALUE_2, VALUE_3, VALUE_4, NONE)

OMNI_ENUM_ASSIGNED(my_enum, VALUE_10 = 10, VALUE_20 = 20, NONE = 0)
OMNI_ENUM_DEFAULT(VALUE_20)
OMNI_ENUM_ASSIGNED_PARSERS(VALUE_10, VALUE_20)
OMNI_ENUM_END // end definition

OMNI_ENUM_DEFINE(other_enum, X, Y, Z)
OMNI_ENUM_DEFAULT(Y)
OMNI_ENUM_END // end definition

class Foo {
    public:
        OMNI_ENUM(InnerEnum, // name
            J, // default
            A, B, C, D, E, F, G, H, I, J, K, NONE // enum values
        )

        InnerEnum val;

        Foo() : val(InnerEnum::B)
        {
        }
};

template < typename ENUM >
void print(const ENUM& val, const std::string& good_parse, const std::string& bad_parse)
{
    ENUM tval;
    std::cout <<
        "enum = " << val << std::endl <<
        "value = " << val.value() << std::endl <<
        "to_string = " << val.to_string() << std::endl <<
        "std::string = " << static_cast<std::string>(val) << std::endl <<
        "uint32_t = " << static_cast<uint32_t>(val) << std::endl <<
        "val.count = " << val.count() << std::endl <<
        "ENUM::COUNT() = " << ENUM::COUNT() << std::endl <<
        "ENUM::DEFAULT_VALUE() = " << ENUM::DEFAULT_VALUE() << std::endl <<
        "ENUM::try_parse(" << good_parse << ") = " << (ENUM::try_parse(good_parse, tval) ? "good" : "bad") << std::endl <<
        "ENUM::try_parse(" << bad_parse << ") = " << (ENUM::try_parse(bad_parse, tval) ? "good" : "bad") << std::endl
    << std::endl;
}

int main(int argc, char* argv[])
{
    Foo foo;
    Foo::InnerEnum fe;
    easy_enum ee = easy_enum::VALUE_3;
    my_enum me = my_enum::VALUE_20;
    other_enum oe;

    print(foo.val, "A", "Z");
    print(fe, "NONE", "L");
    print(ee, "VALUE_1", "VALUE_5");
    print(me, "VALUE_20", "NONE");
    print(oe, "Z", "A");

    return 0;
}
