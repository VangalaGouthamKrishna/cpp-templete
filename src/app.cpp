#include <mosaiqpp/app.hpp>
#include <mosaiqpp/intercom/publication.hpp>

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <cstddef>
#include <algorithm>


class PublisherApp : public MosaiqSdk::CyclicApp
{
public:
  PublisherApp(MosaiqSdk::Intercom::Broker&& broker)
    : MosaiqSdk::CyclicApp{std::move(broker)}
    , m_cycleCount{0}
    , m_int8_t_Pub{getBroker().template publish<int8_t>("int8_t")}
    , m_uint8_t_Pub{getBroker().template publish<uint8_t>("uint8_t")}
    , m_int16_t_Pub{getBroker().template publish<int16_t>("int16_t")}
    , m_uint16_t_Pub{getBroker().template publish<uint16_t>("uint16_t")}
    , m_int32_t_Pub{getBroker().template publish<int32_t>("int32_t")}
    , m_uint32_t_Pub{getBroker().template publish<uint32_t>("uint32_t")}
    , m_int64_t_Pub{getBroker().template publish<int64_t>("int64_t")}
    , m_uint64_t_Pub{getBroker().template publish<uint64_t>("uint64_t")}
    , m_float_Pub{getBroker().template publish<float>("float")}
    , m_double_Pub{getBroker().template publish<double>("double")}
    , m_stringPub{getBroker().template publish<std::string>("string")}
     , m_vectorPub{getBroker().template publish<std::vector<std::byte>>("vector")}
  {}

  void onCyclicExecution()
  {
    ++m_cycleCount;
    m_int8_t_Pub.write(m_cycleCount);
    m_uint8_t_Pub.write(m_cycleCount);
    m_int16_t_Pub.write(m_cycleCount);
    m_uint16_t_Pub.write(m_cycleCount);
    m_int32_t_Pub.write(m_cycleCount);
    m_uint32_t_Pub.write(m_cycleCount);
    m_int64_t_Pub.write(m_cycleCount);
    m_uint64_t_Pub.write(m_cycleCount);
    m_float_Pub.write(m_cycleCount);
    m_double_Pub.write(m_cycleCount);

    std::stringstream sstr;
    sstr << "0x" << std::hex << std::setfill('0') << std::setw(8) << m_cycleCount;
    m_stringPub.write(sstr.str());

    auto numberAsString = sstr.str();
    std::vector<std::byte> bytes(numberAsString.size());
    std::transform(std::begin(numberAsString), std::end(numberAsString), std::begin(bytes), [](auto charater){
      return static_cast<std::byte>(charater);
    });
    m_vectorPub.write(bytes);
  }

private:
  uint32_t m_cycleCount;
  MosaiqSdk::Intercom::Publication<int8_t> m_int8_t_Pub;
  MosaiqSdk::Intercom::Publication<uint8_t> m_uint8_t_Pub;
  MosaiqSdk::Intercom::Publication<int16_t> m_int16_t_Pub;
  MosaiqSdk::Intercom::Publication<uint16_t> m_uint16_t_Pub;
  MosaiqSdk::Intercom::Publication<int32_t> m_int32_t_Pub;
  MosaiqSdk::Intercom::Publication<uint32_t> m_uint32_t_Pub;
  MosaiqSdk::Intercom::Publication<int64_t> m_int64_t_Pub;
  MosaiqSdk::Intercom::Publication<uint64_t> m_uint64_t_Pub;
  MosaiqSdk::Intercom::Publication<float> m_float_Pub;
  MosaiqSdk::Intercom::Publication<double> m_double_Pub;
  MosaiqSdk::Intercom::Publication<std::string> m_stringPub;
  MosaiqSdk::Intercom::Publication<std::vector<std::byte>> m_vectorPub;
};

MOSAIQ_DECLARE_APP(PublisherApp);