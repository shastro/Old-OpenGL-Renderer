#ifndef UTILS_H
#define UTILS_H
/* To store small helper utility functions that don't fit into a more 
	specialized header */

/* Helper function for converting json values to std::strings*/
inline std::string to_string(const json &j)
{	

    if (j.type() == json::value_t::string) {
    	//std::cout << "bruh3" << std::endl;
        return j.get<std::string>();
    }

    return j.dump();
}

#endif