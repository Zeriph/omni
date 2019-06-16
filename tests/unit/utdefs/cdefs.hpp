#if !defined(UT_NAME)
    #error You must define the UT_NAME unit test name
#endif

#if defined(UT_ROOT_NS)
    #define UT_FQN omni::UT_ROOT_NS::UT_NAME
#else
    #define UT_FQN omni::UT_NAME
#endif

#if !defined(UT_DESC)
    #define UT_TMP_DESC OMNI_STRW("Tests the functionality within the ") OMNI_STRW(OMNI_DEF2STR(UT_FQN))
    #if defined(UT_ISNS)
        #define UT_DESC UT_TMP_DESC OMNI_STRW(" namespace")
    #else
        #define UT_DESC UT_TMP_DESC OMNI_STRW(" class")
    #endif
    #define UT_TDESC UT_DESC
#else
    #define UT_TDESC OMNI_STRW("") OMNI_STRW(UT_DESC) OMNI_STRW("")
#endif

#if defined(UT_ISNS)
    #define UT_INFO_TEST() printl("Not applicable to this unit")
#else
    #define UT_INFO_TEST() print_info(UT_FQN)
#endif

#define M_LIST_ADD(cnm, desc) this->m_list[this->m_list.size()] = omni::ut(this->m_list.size(), omni::callback::bind<UT_CNAME, &UT_CNAME::cnm>(this), OMNI_STRW(OMNI_DEF2STR(cnm)), OMNI_STRW(desc))
#define UT_CNAME OMNI_DEFCONCAT(ut_, UT_NAME)
#define UT_CLASS_OBJ OMNI_DEFCONCAT(obj_, UT_NAME)
#define UT_CLASS_DEF UT_CNAME : omni::ut_base
#define UT_CLASS_CTOR() UT_CNAME() : omni::ut_base(OMNI_STRW(OMNI_DEF2STR(UT_NAME)), UT_TDESC)
#define UT_CLASS_DTOR() virtual ~UT_CNAME()
#define UT_CLASS_STATIC_INSTANCE static UT_CNAME UT_CLASS_OBJ;
