#ifndef GRAPH_H
#define GRAPH_H
/**
 *	\file graph.h
 *
 * 	This file is subject to the terms and conditions defined in
 * 	files 'BSD.txt' and 'GPL.txt'. For a list of authors see file 'AUTHORS'.
 */

//Include the BGL/Graphviz stuff from boost
#include <boost/graph/graphviz.hpp>
#include <boost/graph/iteration_macros.hpp>

#include <iosfwd>
#include <string>
#include <set>

struct FlowGraph {
	public:
		FlowGraph(std::string localIPLabel = "", std::string localIPShape = "", std::string protocolLabel = "", std::string protocolShape = "",
		      std::string localPortLabel = "", std::string localPortShape = "", std::string localPort2RemotePortLabel = "",
		      std::string localPort2RemotePortDirection = "", std::string localPort2RemotePortColor = "", std::string remotePortLabel = "",
		      std::string remotePortShape = "", std::string remotePort2RemoteIPLabel = "", std::string remotePort2RemoteIPColor = "", std::string remoteIPLabel =
		            "", std::string remoteIPShape = "");
		bool operator==(const FlowGraph &other) const;
		bool operator<(const FlowGraph &other) const;

		std::ostream& print(std::ostream &os) const;

		std::string localIPLabel;
		std::string localIPShape;
		std::string protocolLabel;
		std::string protocolShape;
		std::string localPortLabel;
		std::string localPortShape;
		std::string localPort2RemotePortLabel;
		std::string localPort2RemotePortDirection;
		std::string localPort2RemotePortColor;
		std::string remotePortLabel;
		std::string remotePortShape;
		std::string remotePort2RemoteIPLabel;
		std::string remotePort2RemoteIPColor;
		std::string remoteIPLabel;
		std::string remoteIPShape;
};

class DotGraph {
	private:
		// This is needed for the Boost/Graphviz stuff
		struct graph_name_t {
				typedef boost::graph_property_tag kind;
		};
		struct graph_rankdir_t {
				typedef boost::graph_property_tag kind;
		};
		struct graph_rank_t {
				typedef boost::graph_property_tag kind;
		};
		struct graph_draw_t {
				typedef boost::graph_property_tag kind;
		};
		struct graph_bb_t {
				typedef boost::graph_property_tag kind;
		};
		struct graph_xdotversion_t {
				typedef boost::graph_property_tag kind;
		};
		struct graph_shape_t {
				typedef boost::graph_property_tag kind;
		};
		struct graph_style_t {
				typedef boost::graph_property_tag kind;
		};

		struct vertex_url_t {
				typedef boost::vertex_property_tag kind;
		};
		struct vertex_fontsize_t {
				typedef boost::vertex_property_tag kind;
		};
		struct vertex_label_t {
				typedef boost::vertex_property_tag kind;
		};
		struct vertex_shape_t {
				typedef boost::vertex_property_tag kind;
		};
		struct vertex_draw_t {
				typedef boost::vertex_property_tag kind;
		};
		struct vertex_ldraw_t {
				typedef boost::vertex_property_tag kind;
		};
		struct vertex_height_t {
				typedef boost::vertex_property_tag kind;
		};
		struct vertex_width_t {
				typedef boost::vertex_property_tag kind;
		};
		struct vertex_pos_t {
				typedef boost::vertex_property_tag kind;
		};
		struct vertex_style_t {
				typedef boost::vertex_property_tag kind;
		};
		struct vertex_rolnum_t {
				typedef boost::vertex_property_tag kind;
		};
		struct vertex_ip_t {
				typedef boost::vertex_property_tag kind;
		};
		struct vertex_fontname_t {
				typedef boost::vertex_property_tag kind;
		};

		struct edge_dir_t {
				typedef boost::edge_property_tag kind;
		};
		struct edge_label_t {
				typedef boost::edge_property_tag kind;
		};
		struct edge_style_t {
				typedef boost::edge_property_tag kind;
		};
		struct edge_draw_t {
				typedef boost::edge_property_tag kind;
		};
		struct edge_hdraw_t {
				typedef boost::edge_property_tag kind;
		};
		struct edge_ldraw_t {
				typedef boost::edge_property_tag kind;
		};
		struct edge_tdraw_t {
				typedef boost::edge_property_tag kind;
		};
		struct edge_pos_t {
				typedef boost::edge_property_tag kind;
		};
		struct edge_lp_t {
				typedef boost::edge_property_tag kind;
		};

	public:
		// Vertex properties
		typedef boost::property<boost::vertex_name_t, std::string, boost::property<boost::vertex_color_t, std::string, boost::property<vertex_url_t, std::string,
		      boost::property<vertex_fontsize_t, int, boost::property<vertex_label_t, std::string, boost::property<vertex_draw_t, std::string, boost::property<
		            vertex_ldraw_t, std::string, boost::property<vertex_height_t, double, boost::property<vertex_width_t, double, boost::property<vertex_pos_t,
		                  std::string, boost::property<vertex_style_t, std::string, boost::property<vertex_shape_t, std::string, boost::property<vertex_rolnum_t,
		                        signed int, boost::property<vertex_ip_t, std::string, boost::property<vertex_fontname_t, std::string> > > > > > > > > > > > > > >
		      VertexProperty;

		// Edge properties
		typedef boost::property<boost::edge_color_t, std::string, boost::property<edge_dir_t, std::string, boost::property<edge_label_t, std::string,
		      boost::property<edge_style_t, std::string, boost::property<edge_draw_t, std::string, boost::property<edge_pos_t, std::string, boost::property<
		            edge_hdraw_t, std::string, boost::property<edge_tdraw_t, std::string, boost::property<edge_ldraw_t, std::string, boost::property<edge_lp_t,
		                  std::string> > > > > > > > > > EdgeProperty;

		// Graph properties
		typedef boost::property<boost::graph_name_t, std::string, boost::property<graph_rankdir_t, std::string, boost::property<graph_rank_t, std::string,
		      boost::property<graph_draw_t, std::string, boost::property<graph_bb_t, std::string, boost::property<graph_xdotversion_t, std::string,
		            boost::property<graph_shape_t, std::string, boost::property<graph_style_t, std::string> > > > > > > > GraphProperty;

		// adjacency_list-based type
		typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperty, EdgeProperty, GraphProperty> BoostGraph;

		// Construct an empty graph and prepare the dynamic_property_maps.
		BoostGraph graph; ///< Our BGL graph
		boost::dynamic_properties dp; ///< Map for all the dynamic properties

		boost::property_map<BoostGraph, boost::vertex_name_t>::type vertices_name;
		boost::property_map<BoostGraph, vertex_url_t>::type vertices_url;
		boost::property_map<BoostGraph, vertex_fontsize_t>::type vertices_fontsize;
		boost::property_map<BoostGraph, vertex_label_t>::type vertices_label;
		boost::property_map<BoostGraph, vertex_shape_t>::type vertices_shape;
		boost::property_map<BoostGraph, vertex_draw_t>::type vertices_draw;
		boost::property_map<BoostGraph, vertex_ldraw_t>::type vertices_ldraw;
		boost::property_map<BoostGraph, vertex_height_t>::type vertices_height;
		boost::property_map<BoostGraph, vertex_width_t>::type vertices_width;
		boost::property_map<BoostGraph, vertex_pos_t>::type vertices_pos;
		boost::property_map<BoostGraph, vertex_style_t>::type vertices_style;
		boost::property_map<BoostGraph, vertex_rolnum_t>::type vertices_rolnum;
		boost::property_map<BoostGraph, vertex_ip_t>::type vertices_ip;
		boost::property_map<BoostGraph, vertex_fontname_t>::type vertex_fontname;

		boost::property_map<BoostGraph, boost::edge_color_t>::type edges_color;
		boost::property_map<BoostGraph, edge_dir_t>::type edges_dir;
		boost::property_map<BoostGraph, edge_label_t>::type edges_label;
		boost::property_map<BoostGraph, edge_style_t>::type edges_style;
		boost::property_map<BoostGraph, edge_draw_t>::type edges_draw;
		boost::property_map<BoostGraph, edge_pos_t>::type edges_pos;
		boost::property_map<BoostGraph, edge_hdraw_t>::type edges_hdraw;
		boost::property_map<BoostGraph, edge_ldraw_t>::type edges_ldraw;
		boost::property_map<BoostGraph, edge_tdraw_t>::type edges_tdraw;
		boost::property_map<BoostGraph, edge_lp_t>::type edges_lp;

		boost::graph_property<BoostGraph, graph_name_t>::type graph_name;
		boost::graph_property<BoostGraph, graph_rankdir_t>::type graph_rankdir;
		boost::graph_property<BoostGraph, graph_draw_t>::type graph_draw;
		boost::graph_property<BoostGraph, graph_bb_t>::type graph_bb;
		boost::graph_property<BoostGraph, graph_xdotversion_t>::type graph_xdotversion;
		boost::graph_property<BoostGraph, graph_shape_t>::type graph_shape;
		boost::graph_property<BoostGraph, graph_style_t>::type graph_style;

		typedef boost::graph_traits<BoostGraph>::vertex_iterator GraphVertexIterator;
		typedef boost::graph_traits<BoostGraph>::vertex_descriptor Vertex;
		typedef boost::graph_traits<BoostGraph>::edge_iterator GraphEdgeIterator;
		typedef boost::graph_traits<BoostGraph>::edge_descriptor Edge;

	public:
		DotGraph(std::ifstream & dotInputStream);
		bool equal(DotGraph & other);
		bool isomorphism(DotGraph & other);
		void buildFlowset(Vertex v, FlowGraph &prototype, unsigned int space, std::multiset<FlowGraph> &results);

	private:
		void prepareGraphProperties();
		static GraphVertexIterator findLocalIP(DotGraph &graph);
		void importDotGraph(std::ifstream & dotInputStream);

};

#endif // GRAPH_H
