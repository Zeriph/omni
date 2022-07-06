#if defined(OMNI_UTUA) || defined(OMNI_UT_CRYPTO)

#define UT_NAME crypto
#define UT_ROOT_NS crypto
#define UT_ISNS true
#define UT_DESC "Tests the various functionality of the omni::crypto namespace"
#include <utdefs/unit_test.hpp>

class UT_CLASS_DEF
{
    public:
        UT_CLASS_CTOR()
        {
            M_LIST_ADD(md5, "test the functionality in omni::crypto::md5");
            M_LIST_ADD(sha1, "test the functionality in omni::crypto::sha1");
            M_LIST_ADD(sha56, "test the functionality in omni::crypto::sha256");
            M_LIST_ADD(base64, "test the functionality in omni::crypto::base64");
        }
        
        UT_CLASS_DTOR() {}

        void info_test()
        {
            print_info(omni::crypto::md5);
            print_info(omni::crypto::sha1);
            print_info(omni::crypto::sha256);
        }
        
        void base_test()
        {
            md5(); printl("");
            sha1(); printl("");
            sha56(); printl("");
        }

        void md5()
        {
            try {
                std::string txt = OMNI_PATH_ROOT + omni::io::path::combine("Code", "omni", "tests", "unit", "data", "hash.txt");
                std::string zip = OMNI_PATH_ROOT + omni::io::path::combine("Code", "omni", "tests", "unit", "data", "hash.zip");
                std::string dat = "test text";
                cprintv("txt = ", txt);
                cprintv("zip = ", zip);
                cprintv("dat = ", dat);

                omni::crypto::md5 hash_txt(txt, omni::crypto::hash_type::TEXT_FILE);
                omni::crypto::md5 hash_zip(zip, omni::crypto::hash_type::TEXT_FILE);
                omni::crypto::md5 hash_txt_bin(txt, omni::crypto::hash_type::BINARY_FILE);
                omni::crypto::md5 hash_zip_bin(zip, omni::crypto::hash_type::BINARY_FILE);
                test("hash_txt", hash_txt, "54b0c58c7ce9f2a8b551351102ee0938");
                test("hash_zip", hash_zip, "4ca0babac7e3c4891628529afa74572b");
                test("hash_txt_bin", hash_txt_bin, "54b0c58c7ce9f2a8b551351102ee0938");
                test("hash_zip_bin", hash_zip_bin, "4ca0babac7e3c4891628529afa74572b");
                test("omni::crypto::md5::compute_file_hash(txt)", omni::crypto::md5::compute_file_hash(txt), "54b0c58c7ce9f2a8b551351102ee0938");
                test("omni::crypto::md5::compute_file_hash(zip)", omni::crypto::md5::compute_file_hash(zip), "4ca0babac7e3c4891628529afa74572b");
                test("omni::crypto::md5::compute_binary_file_hash(txt)", omni::crypto::md5::compute_binary_file_hash(txt), "54b0c58c7ce9f2a8b551351102ee0938");
                test("omni::crypto::md5::compute_binary_file_hash(zip)", omni::crypto::md5::compute_binary_file_hash(zip), "4ca0babac7e3c4891628529afa74572b");
                
                omni::crypto::md5 hash_dat(dat, omni::crypto::hash_type::STRING);
                omni::crypto::md5 hash_str(omni::crypto::md5::compute_hash(dat));
                test("hash_dat", hash_dat, "1e2db57dd6527ad4f8f281ab028d2c70");
                test("hash_str", hash_str, "1e2db57dd6527ad4f8f281ab028d2c70");
                test("omni::crypto::md5::compute_hash(dat)", omni::crypto::md5::compute_hash(dat), "1e2db57dd6527ad4f8f281ab028d2c70");
            } catch (const std::exception& ex) {
                printv("Exception: ", ex.what());
            } catch (...) {
                printl("Unknown error");
            }
        }

        void sha1()
        {
            try {
                std::string txt = OMNI_PATH_ROOT + omni::io::path::combine("Code", "omni", "tests", "unit", "data", "hash.txt");
                std::string zip = OMNI_PATH_ROOT + omni::io::path::combine("Code", "omni", "tests", "unit", "data", "hash.zip");
                std::string dat = "test text\n";
                cprintv("txt = ", txt);
                cprintv("zip = ", zip);
                cprintv("dat = ", dat);

                omni::crypto::sha1 hash_txt(txt, omni::crypto::hash_type::TEXT_FILE);
                omni::crypto::sha1 hash_zip(zip, omni::crypto::hash_type::TEXT_FILE);
                omni::crypto::sha1 hash_txt_bin(txt, omni::crypto::hash_type::BINARY_FILE);
                omni::crypto::sha1 hash_zip_bin(zip, omni::crypto::hash_type::BINARY_FILE);
                test("hash_txt", hash_txt, "fa26be19de6bff93f70bc2308434e4a440bbad02");
                test("hash_zip", hash_zip, "d564ec8324f5657425145faac99f3c36da869d71");
                test("hash_txt_bin", hash_txt_bin, "fa26be19de6bff93f70bc2308434e4a440bbad02");
                test("hash_zip_bin", hash_zip_bin, "d564ec8324f5657425145faac99f3c36da869d71");
                test("omni::crypto::sha1::compute_file_hash(txt)", omni::crypto::sha1::compute_file_hash(txt), "fa26be19de6bff93f70bc2308434e4a440bbad02");
                test("omni::crypto::sha1::compute_file_hash(zip)", omni::crypto::sha1::compute_file_hash(zip), "d564ec8324f5657425145faac99f3c36da869d71");
                test("omni::crypto::sha1::compute_binary_file_hash(txt)", omni::crypto::sha1::compute_binary_file_hash(txt), "fa26be19de6bff93f70bc2308434e4a440bbad02");
                test("omni::crypto::sha1::compute_binary_file_hash(zip)", omni::crypto::sha1::compute_binary_file_hash(zip), "d564ec8324f5657425145faac99f3c36da869d71");
                
                omni::crypto::sha1 hash_dat(dat, omni::crypto::hash_type::STRING);
                omni::crypto::sha1 hash_str(omni::crypto::sha1::compute_hash(dat));
                test("hash_dat", hash_dat, "be85789dc7301b4060b3ffd7e16aa7b00cd4670f");
                test("hash_str", hash_str, "be85789dc7301b4060b3ffd7e16aa7b00cd4670f");
                test("omni::crypto::sha1::compute_hash(dat)", omni::crypto::sha1::compute_hash(dat), "be85789dc7301b4060b3ffd7e16aa7b00cd4670f");
            } catch (const std::exception& ex) {
                printv("Exception: ", ex.what());
            } catch (...) {
                printl("Unknown error");
            }
        }

        void sha56()
        {
            try {
                std::string txt = OMNI_PATH_ROOT + omni::io::path::combine("Code", "omni", "tests", "unit", "data", "hash.txt");
                std::string zip = OMNI_PATH_ROOT + omni::io::path::combine("Code", "omni", "tests", "unit", "data", "hash.zip");
                std::string dat = "test text\n";
                cprintv("txt = ", txt);
                cprintv("zip = ", zip);
                cprintv("dat = ", dat);

                omni::crypto::sha256 hash_txt(txt, omni::crypto::hash_type::TEXT_FILE);
                omni::crypto::sha256 hash_zip(zip, omni::crypto::hash_type::TEXT_FILE);
                omni::crypto::sha256 hash_txt_bin(txt, omni::crypto::hash_type::BINARY_FILE);
                omni::crypto::sha256 hash_zip_bin(zip, omni::crypto::hash_type::BINARY_FILE);
                test("hash_txt", hash_txt, "2e99758548972a8e8822ad47fa1017ff72f06f3ff6a016851f45c398732bc50c");
                test("hash_zip", hash_zip, "c1f4da24a4acf4ba1200f8fb281008dee7ea3281c7ba58b9a7ac055d1449ebd6");
                test("hash_txt_bin", hash_txt_bin, "2e99758548972a8e8822ad47fa1017ff72f06f3ff6a016851f45c398732bc50c");
                test("hash_zip_bin", hash_zip_bin, "c1f4da24a4acf4ba1200f8fb281008dee7ea3281c7ba58b9a7ac055d1449ebd6");
                test("omni::crypto::sha256::compute_file_hash(txt)", omni::crypto::sha256::compute_file_hash(txt), "2e99758548972a8e8822ad47fa1017ff72f06f3ff6a016851f45c398732bc50c");
                test("omni::crypto::sha256::compute_file_hash(zip)", omni::crypto::sha256::compute_file_hash(zip), "c1f4da24a4acf4ba1200f8fb281008dee7ea3281c7ba58b9a7ac055d1449ebd6");
                test("omni::crypto::sha256::compute_binary_file_hash(txt)", omni::crypto::sha256::compute_binary_file_hash(txt), "2e99758548972a8e8822ad47fa1017ff72f06f3ff6a016851f45c398732bc50c");
                test("omni::crypto::sha256::compute_binary_file_hash(zip)", omni::crypto::sha256::compute_binary_file_hash(zip), "c1f4da24a4acf4ba1200f8fb281008dee7ea3281c7ba58b9a7ac055d1449ebd6");
                
                omni::crypto::sha256 hash_dat(dat, omni::crypto::hash_type::STRING);
                omni::crypto::sha256 hash_str(omni::crypto::sha256::compute_hash(dat));
                test("hash_dat", hash_dat, "c2a4f4903509957d138e216a6d2c0d7867235c61088c02ca5cf38f2332407b00");
                test("hash_str", hash_str, "c2a4f4903509957d138e216a6d2c0d7867235c61088c02ca5cf38f2332407b00");
                test("omni::crypto::sha256::compute_hash(dat)", omni::crypto::sha256::compute_hash(dat), "c2a4f4903509957d138e216a6d2c0d7867235c61088c02ca5cf38f2332407b00");
            } catch (const std::exception& ex) {
                printv("Exception: ", ex.what());
            } catch (...) {
                printl("Unknown error");
            }
        }

        void base64()
        {
            std::string in_file = "/Code/omni/tests/misc/pencil.gif";
            std::string data = omni::io::file::get_contents(in_file);
            std::string encoded = omni::crypto::base64::encode(data);
            test("base64_encode", encoded, "R0lGODlhQABAAIABAAAAAP///yH5BAEKAAEALAAAAABAAEAAAALMjI+py60AgZu00oit3hN7yYXc94nmRZbnmqQpC7sufMoybdovLuok3/NlgA7IQ2gkMoYIJEjZ8hx10Kk0eqs2Z9if9kDtMr9Ca/IbcFrRBucZ/CS732z4nM6+X+v6PbrvpwU4JjiIB2V4qJQYV2jIlwj5mBdJOflXiXkpt+k4KPlpGao5ylnqCQiaWpd2KjrHKoYUa+bDeqh2i2sbS9hmQ6si60sasbAT7CVLaye8pVjsDMfcjEx9HHZda639y9vd+g0ODL5d3tF4zlAAADs=");
            

            std::string out_file = "/Code/omni/tests/misc/pencil_2.gif";
            std::string enc_str = "R0lGODlhQABAAIABAAAAAP///yH5BAEKAAEALAAAAABAAEAAAALMjI+py60AgZu00oit3hN7yYXc94nmRZbnmqQpC7sufMoybdovLuok3/NlgA7IQ2gkMoYIJEjZ8hx10Kk0eqs2Z9if9kDtMr9Ca/IbcFrRBucZ/CS732z4nM6+X+v6PbrvpwU4JjiIB2V4qJQYV2jIlwj5mBdJOflXiXkpt+k4KPlpGao5ylnqCQiaWpd2KjrHKoYUa+bDeqh2i2sbS9hmQ6si60sasbAT7CVLaye8pVjsDMfcjEx9HHZda639y9vd+g0ODL5d3tF4zlAAADs=";
            
            std::deque<uint8_t> decoded = omni::crypto::base64::decode(enc_str);
            omni::io::file::write(out_file, decoded);

            std::vector<unsigned char> buff;
            omni::crypto::base64::decode(enc_str, buff);
            omni::io::file::write("/Code/omni/tests/misc/pencil_3.gif", buff);
        }
};

#include <utdefs/udefs.hpp> // static instance def'd and clean up #def's

#endif // OMNI_UT_CRYPTO
