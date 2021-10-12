#include <mosaiqpp/app.hpp>
#include <mosaiqpp/intercom/publication.hpp>
#include <mosaiqpp/intercom/subscription.hpp>

#include <iomanip>
#include <sstream>
#include <string>

/// The class "YourClass" must publicly derive from the provided MosaiqSdk::CyclicApp
/// It may contain members to provide Real Time Intercommunication functionality and
/// it may also contain other members to be used for custom processing. The functions
/// YourClass::onInitialization(), YourClass::onCyclicExecution() and YourClass::onExit()
/// will be considered for the main functionality of the Mosaiq Runtime and must be publicly
/// accessible.
class YourClass : public MosaiqSdk::CyclicApp
{
public:
  /// The constructor of YourClass must move the broker to its base class. You can use the broker
  /// via MosaiqSdk::CyclicApp::getBroker() and then initialize publication and subscription members
  /// with the handles that are returned from MosaiqSdk::Intercom::Broker::publish() and
  /// MosaiqSdk::Intercom::Broker::subscribe() functions. Custom members can also be initialized here.
  YourClass(MosaiqSdk::Intercom::Broker &&broker)
      : MosaiqSdk::CyclicApp{std::move(broker)}, m_integralPub{getBroker().template publish<uint32_t>("cycleCounter")}, m_cycleCount{0}
      // string "cycleCounter" is the topic name which is required to publish or subscribe that particular 
      // datatype's data and to create web socket stream
      // NOTE: topic name should be unique across the cyclic apps in that machine and
      // topic name cannot be an empty string
      // NOTE: the subscription of an app must match the datatype and topic name of the publication app
      // Possible datatypes are:
      // "int8_t", "uint8_t", "int16_t", "uint16_t", "int32_t", "uint32_t", "int64_t", "uint64_t",
      // "float", "double", "std::string", "std::vector<std::byte>"
  {
  }
  /// You can run procedures inside here, that need to be run once before the cyclic execution.
  /// This step is optional.
  void onInitialization()
  {
    m_cycleCount = 12; // set the value m_cycleCount to 12 before doing the cyclic execution.
  }
  /// The procedure inside this function is periodically called according to a preconfigured cycle time.
  /// You can do any calculations and processing based on members of YourClass or other
  /// variables and values here.
  void onCyclicExecution()
  {
    ++m_cycleCount;
    m_integralPub.write(m_cycleCount);
    // at this point the value of m_cycleCount is written to the topic of m_integralPub (which is
    // cycleCounter) and other apps that subscribed to this topic can read the updated value
  }
  /// You can run procedures inside here, that need to be run once after finishing the cyclic execution. 
  /// This step is optional.
  void onExit()
  {
  }
private:
  uint32_t m_cycleCount;
  /// This is a member to publish integral values of the type uint32_t through the Mosaiq Runtime
  /// Real Time Intercommunication. When the class YourClass is instantiated, this member needs to
  /// be initialized by passing a publication handle of the type MosaiqIntercomPublication*. This
  /// handle can be acquired via a publish through the broker, that is used as a parameter during
  /// construction of "YourClass". MosaiqSdk::CyclicApp::getBroker() provides the broker and it can
  /// then be used to publish by also specifying the type and topic name.
  /// Possible datatypes are:
  /// "int8_t", "uint8_t", "int16_t", "uint16_t", "int32_t", "uint32_t", "int64_t", "uint64_t",
  /// "float", "double", "std::string", "std::vector<std::byte>"
  MosaiqSdk::Intercom::Publication<uint32_t> m_integralPub;
};
/// This macro needs to be called for YourClass to function in the Mosaiq Runtime
MOSAIQ_DECLARE_APP(YourClass);


/************************************ sample publisher app templete ************************************/

/*

 class PublisherApp : public MosaiqSdk::CyclicApp
{
public:
  PublisherApp(MosaiqSdk::Intercom::Broker&& broker)
    : MosaiqSdk::CyclicApp{std::move(broker)}
    , m_cycleCount{0}
    , m_integralPub{getBroker().template publish<uint32_t>("cycleCounter")}
    , m_stringPub{getBroker().template publish<std::string>("cycleCounterHex")}
  {}

  void onInitialization()
  {
  }

  void onCyclicExecution()
  {
    ++m_cycleCount;
    m_integralPub.write(m_cycleCount);

    std::stringstream sstr;
    sstr << "0x" << std::hex << std::setfill('0') << std::setw(8) << m_cycleCount;
    m_stringPub.write(sstr.str());
  }

  void onExit()
  {
  }

private:
  uint32_t m_cycleCount;
  MosaiqSdk::Intercom::Publication<uint32_t> m_integralPub;
  MosaiqSdk::Intercom::Publication<std::string> m_stringPub;
};

MOSAIQ_DECLARE_APP(PublisherApp); 

*/
 
 /************************************ sample subscriber app templete ************************************/

/*

 class SubscriberApp : public MosaiqSdk::CyclicApp
{
public:
  SubscriberApp(MosaiqSdk::Intercom::Broker&& broker)
    : MosaiqSdk::CyclicApp{std::move(broker)}
    , m_cycleCount{0}
    , m_integralSub{getBroker().template subscribe<uint32_t>("cycleCounter")}
    , m_stringSub{getBroker().template subscribe<std::string>("cycleCounterHex")}
  {}

  void onInitialization()
  {
  }

  void onCyclicExecution()
  {
    uint32_t value{0};
    std::string strValue{};
    strValue.reserve(10);
    m_integralSub.read(value);
    m_stringSub.read(strValue);
  }

  void onExit()
  {
  }

private:
  uint32_t m_cycleCount;
  MosaiqSdk::Intercom::Subscription<uint32_t> m_integralSub;
  MosaiqSdk::Intercom::Subscription<std::string> m_stringSub;
};

MOSAIQ_DECLARE_APP(SubscriberApp); 

*/
