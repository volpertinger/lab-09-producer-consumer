// Copyright 2020 Merzlov Nikolay merzlovnik@mail.ru
/*
#include <header.hpp>

using tcp = boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
namespace http = boost::beast::http;

class IMG_founder {
  std::string adress;
  std::string output;
  size_t depth;
  size_t network_threads;
  size_t parser_threads;

 public:
  IMG_founder()
      : adress(),
        output("result.txt"),
        depth(1),
        network_threads(1),
        parser_threads(1) {}

  IMG_founder(std::string& adress_, std::string& output_, size_t& depth_,
              size_t& network_threads_, size_t& parser_threads_)
      : adress(adress_),
        output(output_),
        depth(depth_),
        network_threads(network_threads_),
        parser_threads(parser_threads_) {}

  void set_adress(std::string& adress_) { adress = adress_; }

  void search_for_links(GumboNode* node, std::fstream& out) {
    if (node->type != GUMBO_NODE_ELEMENT) return;
    GumboAttribute* href;

    if (node->v.element.tag == GUMBO_TAG_A &&
        (href = gumbo_get_attribute(&node->v.element.attributes, "href")))
      out << href->value << "\n";

    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
      search_for_links(static_cast<GumboNode*>(children->data[i]), out);
    }
  }

  void start() {
    std::ifstream in(adress, std::ios::in | std::ios::binary);
    if (!in) {
      std::cout << "File " << adress << " not found!\n";
      return;
    }

    std::fstream out(output, std::ios::out);

    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();

    GumboOutput* g_output = gumbo_parse(contents.c_str());
    search_for_links(g_output->root, out);
    gumbo_destroy_output(&kGumboDefaultOptions, g_output);

    //////////
    if (depth == 0 && network_threads && parser_threads) return;
    ///////
  }
};

int main() {
  std::string adress =
      "/home/killoboker/Downloads/1st United States Congress - Wikipedia.html";

  IMG_founder founder;
  founder.set_adress(adress);
  founder.start();


  return 0;
}
*/