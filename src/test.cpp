#include <iostream>
#include <string>
#include <vector>

#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <boost/uuid/random_generator.hpp>

namespace cti
{
  namespace common
  {
    class uuidAlgorithm
    {
      private:
        std::vector<unsigned char> four_;
        std::string eight_;

        void eightToFour()
        {
          int index = 0;
          while ((index = eight_.find('-', index)) != std::string::npos)
          {
            eight_.erase(index, 1);
          }
          for (int i = 0; i < eight_.length(); i++)
          {
            unsigned char c = eight_[i];
            int h = 0, l = 0;
            if (c >= '0' && c <= '9')
            {
              h = c - '0';
            }
            if (c >= 'a' && c <= 'f')
            {
              h = c - 'a' + 10;
            }
            h <<= 4;
            i++;
            if (i >= eight_.length())
            {
              break;
            }

            c = eight_[i];
            if (c >= '0' && c <= '9')
            {
              l = c - '0';
            }
            if (c >= 'a' && c <= 'f')
            {
              l = c - 'a' + 10;
            }

            h |= l;
            four_.push_back(h);
          }
        }

        std::string fourToEight()
        {
          std::string eight;
          int h = 0, l = 0;
          for (int i = 0; i < four_.size(); i++)
          {
            unsigned char c = four_[i];
            h = c & 0xf0;
            h >>= 4;
            l = c & 0x0f;

            if (h >= 0x0a && h <= 0x0f)
            {
              h = h - 0x0a + 'a';
            }
            if (h >= 0 && h <= 9)
            {
              h = h + '0';
            }

            if (l >= 0x0a && l <= 0x0f)
            {
              l = l - 0x0a + 'a';
            }
            if (l >= 0 && l <= 9)
            {
              l = l + '0';
            }
            eight.push_back(h);
            eight.push_back(l);
          }
          eight.insert(8, "-");
          eight.insert(13, "-");
          eight.insert(18, "-");
          eight.insert(23, "-");
          return eight;
        }

        std::string fourToString()
        {
          std::string out;
          for (auto i : four_)
          {
            out.push_back(i);
          }
          return out;
        }

        bool stringToFour(std::string str)
        {
          if (str.size() != 16)
          {
            return false;
          }
          for (auto i : str)
          {
            four_.push_back(static_cast<unsigned char>(i));
          }
          return true;
        }

        bool stringToEight(std::string str)
        {
          if (str.size() != 36)
          {
            return false;
          }
          eight_ = str;
          return true;
        }

      public:
        uuidAlgorithm() {}

        bool setUncompressedUUID(std::string uncompressedUUID) { return stringToEight(uncompressedUUID); }
        bool setCompressedUUID(std::string compressedUUID) { return stringToFour(compressedUUID); }

        std::string getCompressedUUID()
        {
          eightToFour();
          return fourToString();
        }
        std::string getDecompressedUUID() { return fourToEight(); }
    };
  };
};

int main(int argc, char* argv[])
{
  std::string uuid = boost::uuids::to_string(boost::uuids::random_generator()());
  cti::common::uuidAlgorithm compressUUID;

  std::cout << "uuid:\n"
            << uuid << std::endl;
  std::cout << "uuid size: " << uuid.size() << std::endl;

  compressUUID.setUncompressedUUID(uuid);
  std::string compressedUUID = compressUUID.getCompressedUUID();
  std::cout << compressedUUID << std::endl;

  cti::common::uuidAlgorithm decompressUUID;
  decompressUUID.setCompressedUUID(compressedUUID);
  std::string decompressedUUID = decompressUUID.getDecompressedUUID();
  std::cout << decompressedUUID << std::endl;

  return 0;
}
