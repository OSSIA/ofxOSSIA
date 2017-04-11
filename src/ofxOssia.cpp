//
//  ofxOssia.cpp
//  ofxOSSIA
//
//  Created by Thomas Pachoud on 21/02/2017.
//
//
#include <string>

#include "ofxOssia.h"
#include <ossia/ossia.hpp>
#include <ossia/network/common/debug.hpp>
#include "ossia/network/oscquery/oscquery_server.hpp"
#include "ossia/network/oscquery/oscquery_mirror.hpp"
#include "ossia/network/oscquery/detail/http_client.hpp"
#include <memory>
#include <functional>

void ofxOssia::setup(){
    setup("OSCQuery", "ofxOssiaDevice", 3456, 5678);
}

void ofxOssia::setup(const std::string& type,
                     const std::string& localname,
                     int localportOSC, int localPortWS){
    auto& local_proto = static_cast<ossia::net::local_protocol&>(_device.getProtocol());
    
    // declare a distant program as a Minuit device
    local_proto.exposeTo (std::make_unique<ossia::oscquery::oscquery_server_protocol> (localportOSC, localPortWS));
    
    _root_node.setup (_device.getRootNode(), "ossia");
}

void explore(const ossia::net::node_base& node)
{
  for (const ossia::net::node_base* child : node.children_copy())
  {
    if (auto addr = child->getAddress())
    {
	std::cerr << ossia::net::osc_address_string(*addr) << " : "
		  << ossia::value_to_pretty_string(addr->fetchValue()) << "\n";
	addr->pullValue();

    }
    explore(*child);
  }
}

using namespace ossia::oscquery;

void ofxOssia::setup(const std::string& serverName, int serverPortWS, int localPortOSC){
     auto& local_proto = static_cast<ossia::net::local_protocol&>(_device.getProtocol());
     local_proto.exposeTo (std::make_unique<oscquery_mirror_protocol>("ws://"+ serverName +":" + std::to_string(serverPortWS),
								      localPortOSC));
     _device.getProtocol().update(_device);
     explore(_device.getRootNode());
}

void ofxOssia::setup(const std::string& type,
                     const std::string& localname,
                     const std::string& remotename,
                     const std::string& remoteip,
                     int localport, int remoteport){
    
    auto& local_proto = static_cast<ossia::net::local_protocol&>(_device.getProtocol());
    
    // declare a distant program as a Minuit device
    local_proto.exposeTo(std::make_unique<ossia::net::minuit_protocol>(localname, remoteip, localport, remoteport));
    
    _root_node.setup(_device.getRootNode(), "ossia");
}

