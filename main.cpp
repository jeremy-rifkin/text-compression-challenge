#include <assert.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string_view>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>

#define let auto
constexpr std::nullptr_t null = nullptr;

constexpr double magic[27][26] = {
    { 0.001665001665001665, 0.1496836496836497, 0.2524142524142524, 0.36413586413586413, 0.0028305028305028305, 0.037462537462537464, 0.13936063936063936, 0.003663003663003663, 0.25607725607725607, 0.0018315018315018315, 0.09174159174159174, 0.5198135198135199, 0.12337662337662338, 1.0, 0.0014985014985014985, 0.14402264402264403, 0.0004995004995004995, 0.6082251082251082, 0.7352647352647352, 0.7713952713952714, 0.05194805194805195, 0.11655011655011654, 0.045454545454545456, 0.00333000333000333, 0.15434565434565434, 0.008824508824508824, },
    { 0.17753067484662577, 0.03872699386503067, 0.0007668711656441718, 0.0011503067484662577, 1.0, 0.0, 0.0, 0.0003834355828220859, 0.11042944785276074, 0.020322085889570553, 0.0, 0.40299079754601225, 0.005751533742331288, 0.0003834355828220859, 0.31901840490797545, 0.0, 0.0, 0.24348159509202455, 0.03834355828220859, 0.012653374233128834, 0.325920245398773, 0.009969325153374233, 0.0, 0.0, 0.18059815950920247, 0.0, },
    { 0.5969026548672567, 0.0, 0.084070796460177, 0.0008849557522123894, 0.9252212389380531, 0.0, 0.0, 0.765929203539823, 0.24513274336283186, 0.0, 0.32212389380530976, 0.16858407079646018, 0.0, 0.0, 1.0, 0.0, 0.002654867256637168, 0.2721238938053097, 0.010176991150442478, 0.4411504424778761, 0.16106194690265488, 0.0, 0.0, 0.0, 0.02654867256637168, 0.0, },
    { 0.2264775413711584, 0.005673758865248227, 0.004728132387706856, 0.108274231678487, 1.0, 0.011347517730496455, 0.03687943262411347, 0.010874704491725768, 0.6505910165484634, 0.0070921985815602835, 0.0, 0.10685579196217494, 0.01182033096926714, 0.030260047281323876, 0.4699763593380615, 0.0018912529550827422, 0.0, 0.15224586288416075, 0.28416075650118205, 0.013711583924349883, 0.12009456264775414, 0.013711583924349883, 0.009929078014184398, 0.0, 0.12151300236406619, 0.0, },
    { 0.38326514451629934, 0.009634419955127359, 0.16220139897056882, 0.6473538339712287, 0.2824336808763363, 0.06823280981918965, 0.029299194932031147, 0.01623333773261185, 0.07456777088557477, 0.0010558268443975189, 0.010558268443975187, 0.2592054902995909, 0.1899168536360037, 0.6831199683251946, 0.030091065065329287, 0.07100435528573314, 0.010426290088425499, 1.0, 0.4825128678896661, 0.2044344727464696, 0.014121684043816814, 0.1769829747921341, 0.07087237693018344, 0.08261845057410584, 0.11891249835027055, 0.0023756103998944173, },
    { 0.47116052814454484, 0.002779708130646282, 0.0118137595552467, 0.005559416261292564, 0.6198749131341209, 0.32453092425295343, 0.0, 0.0034746351633078527, 0.5343988881167477, 0.0, 0.0, 0.20917303683113272, 0.0, 0.001389854065323141, 1.0, 0.002779708130646282, 0.0, 0.5066018068102849, 0.01389854065323141, 0.2050034746351633, 0.23002084781097984, 0.0, 0.0006949270326615705, 0.0, 0.017373175816539264, 0.0, },
    { 0.46734059097978226, 0.0023328149300155523, 0.0, 0.006220839813374806, 0.916796267496112, 0.0, 0.08709175738724728, 1.0, 0.3693623639191291, 0.0, 0.0, 0.19595645412130638, 0.017107309486780714, 0.09642301710730948, 0.380248833592535, 0.014774494556765163, 0.0, 0.3786936236391913, 0.18429237947122862, 0.04043545878693624, 0.22472783825816486, 0.0, 0.0, 0.0, 0.028771384136858476, 0.0007776049766718507, },
    { 0.3705921004599547, 0.0006570781923048843, 0.0004380521282032562, 0.00014601737606775207, 1.0, 0.0012411476965758926, 7.300868803387604e-05, 0.00014601737606775207, 0.29678031685770606, 0.0, 0.0, 0.0018252172008469008, 0.0013141563846097686, 0.0017522085128130248, 0.13754836825582245, 0.0002190260641016281, 7.300868803387604e-05, 0.023289771482806455, 0.0038694604657954295, 0.06322552383733664, 0.020880484777688543, 0.0, 0.0005840695042710083, 0.0, 0.012922537781996058, 0.0, },
    { 0.06850020601565719, 0.03069633292130202, 0.188504326328801, 0.13988463123197362, 0.11454470539761022, 0.07354758961681088, 0.09404614750721055, 0.0008240626287597857, 0.000927070457354759, 0.0, 0.02976926246394726, 0.1361763494025546, 0.17140502678203542, 1.0, 0.14400494437577255, 0.024927894519983517, 0.001854140914709518, 0.10249278945199836, 0.3479604449938195, 0.4787803873094355, 0.002266172229089411, 0.0645859085290482, 0.0, 0.008446641944787803, 0.0, 0.018438401318500205, },
    { 0.088, 0.0, 0.0, 0.0, 0.404, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.336, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, },
    { 0.037803780378037805, 0.017101710171017102, 0.008100810081008101, 0.0009000900090009, 1.0, 0.0036003600360036, 0.004500450045004501, 0.008100810081008101, 0.48334833483348333, 0.0, 0.0, 0.05490549054905491, 0.0063006300630063005, 0.38253825382538253, 0.0018001800180018, 0.0063006300630063005, 0.0018001800180018, 0.0027002700270027003, 0.1251125112511251, 0.0, 0.018001800180018002, 0.0, 0.0333033303330333, 0.0, 0.023402340234023402, 0.0, },
    { 0.4166666666666667, 0.005997474747474747, 0.008207070707070708, 0.48169191919191917, 1.0, 0.11142676767676768, 0.0022095959595959595, 0.0003156565656565657, 0.7152777777777778, 0.0003156565656565657, 0.03819444444444445, 0.7679924242424242, 0.052398989898989896, 0.0022095959595959595, 0.41792929292929293, 0.022095959595959596, 0.0003156565656565657, 0.023674242424242424, 0.13415404040404041, 0.11900252525252525, 0.10132575757575757, 0.028724747474747476, 0.049873737373737376, 0.0, 0.6202651515151515, 0.0, },
    { 0.44065142499217036, 0.11337300344503602, 0.0015659254619480112, 0.00031318509238960227, 1.0, 0.004697776385844034, 0.0, 0.0, 0.3225806451612903, 0.00031318509238960227, 0.0, 0.0028186658315064203, 0.06451612903225806, 0.008769182586908864, 0.38740995928593797, 0.20012527403695585, 0.0, 0.021609771374882555, 0.08894456623864704, 0.0018791105543376136, 0.11368618853742563, 0.0, 0.0006263701847792045, 0.0, 0.04854368932038835, 0.0, },
    { 0.12877913685668127, 0.004846526655896607, 0.2236325871220863, 0.9919224555735057, 0.6835910454650358, 0.033002538656819756, 1.0, 0.004846526655896607, 0.22986383567966767, 0.0027694438033694898, 0.07200553888760673, 0.08285252711747057, 0.008077544426494346, 0.051696284329563816, 0.5435033464112624, 0.004154165705054235, 0.010154627279021463, 0.0036925917378259868, 0.41010846988229865, 0.6967459035310408, 0.054696515116547426, 0.028617585968151397, 0.006462035541195477, 0.0016155088852988692, 0.10385414262635588, 0.0011539349180706207, },
    { 0.028278132868487314, 0.08367228355607205, 0.09819872167344568, 0.11408096068177416, 0.014913809800503584, 0.7197365872554716, 0.04474142940151075, 0.003873716831299632, 0.06682161533991865, 0.000968429207824908, 0.08270385434824715, 0.2285492930466783, 0.38582219639744336, 1.0, 0.22506294789850861, 0.12415262444315321, 0.0, 0.7420104590354445, 0.18768158047646716, 0.3933759442184776, 0.9943831105946155, 0.12124733681967848, 0.3083478597714507, 0.009103234553554135, 0.01820646910710827, 0.004067402672864613, },
    { 0.7300832342449465, 0.0005945303210463733, 0.0, 0.0, 1.0, 0.0023781212841854932, 0.0, 0.10523186682520809, 0.2740784780023781, 0.0, 0.0, 0.4702734839476813, 0.0047562425683709865, 0.010107015457788348, 0.5891795481569561, 0.3501783590963139, 0.0, 0.5695600475624257, 0.12663495838287753, 0.20154577883472058, 0.18370986920332938, 0.0, 0.0017835909631391202, 0.0, 0.028537455410225922, 0.0, },
    { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, },
    { 0.24676125848241826, 0.007094386181369525, 0.029765576804441703, 0.1135101789019124, 1.0, 0.015885256014805674, 0.03485502776064158, 0.02313386798272671, 0.3258790869833436, 0.0, 0.04426280074028378, 0.05351634793337446, 0.06153608883405305, 0.06523750771128933, 0.35502776064157926, 0.014805675508945095, 0.00015422578655151142, 0.07449105490438002, 0.20635410240592228, 0.20882171499074645, 0.08281924737816163, 0.015885256014805674, 0.011721159777914868, 0.00015422578655151142, 0.16455891425046268, 0.0, },
    { 0.2759701132803085, 0.002410219329959026, 0.11328030850807423, 0.0028922631959508315, 0.6529284164859002, 0.009881899252832008, 0.00457941672692215, 0.32176428054953, 0.3947939262472885, 0.0, 0.0274765003615329, 0.0829115449505905, 0.06290672451193059, 0.02386117136659436, 0.3335743552663292, 0.15859243191130393, 0.0091588334538443, 0.001205109664979513, 0.33550253073029646, 1.0, 0.18076644974692696, 0.0, 0.038322487346348515, 0.0, 0.03567124608339359, 0.0, },
    { 0.0980215203054495, 0.0011801457827143353, 0.011246095105866018, 0.0006247830614370011, 0.25484206872613674, 0.0016660881638320027, 0.00020826102047900034, 1.0, 0.19514057618882333, 0.0, 0.0, 0.036376258243665395, 0.00388753904894134, 0.0014578271433530025, 0.28934397778549115, 0.0007636237417563346, 0.0, 0.09413398125650815, 0.06289482818465811, 0.05206525511975009, 0.048247136410968415, 0.0, 0.02457480041652204, 0.0, 0.06386671294689344, 0.0, },
    { 0.2034313725490196, 0.13088235294117648, 0.22303921568627452, 0.09607843137254903, 0.19117647058823528, 0.031862745098039214, 0.39950980392156865, 0.0, 0.12794117647058822, 0.0, 0.0, 0.8073529411764706, 0.17598039215686276, 0.6323529411764706, 0.021568627450980392, 0.29411764705882354, 0.0, 0.8588235294117647, 0.6818627450980392, 1.0, 0.0, 0.007352941176470588, 0.0, 0.00392156862745098, 0.0058823529411764705, 0.0029411764705882353, },
    { 0.0952836201402167, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.1701720841300191, 0.0, 0.0, 0.0, 0.0, 0.00031867431485022306, 0.09273422562141491, 0.0, 0.0, 0.0009560229445506692, 0.0, 0.0, 0.0012746972594008922, 0.0, 0.0, 0.0, 0.011153601019757807, 0.0, },
    { 1.0, 0.0, 0.0005765350245027386, 0.011242432977803401, 0.476217930239262, 0.0008648025367541078, 0.0, 0.5615451138656673, 0.5756702219659844, 0.0, 0.0017296050735082155, 0.016431248198328047, 0.0002882675122513693, 0.13000864802536755, 0.35802825021620066, 0.0011530700490054772, 0.0, 0.050446814643989625, 0.04900547708273278, 0.0017296050735082155, 0.0005765350245027386, 0.0, 0.0008648025367541078, 0.0, 0.002017872585759585, 0.0, },
    { 0.5540540540540541, 0.0, 0.7162162162162162, 0.0, 0.3716216216216216, 0.006756756756756757, 0.0, 0.06756756756756757, 1.0, 0.0, 0.0, 0.006756756756756757, 0.0, 0.0, 0.006756756756756757, 0.7635135135135135, 0.006756756756756757, 0.0, 0.006756756756756757, 0.9256756756756757, 0.14864864864864866, 0.0, 0.02702702702702703, 0.0, 0.10810810810810811, 0.0, },
    { 0.02442635085122132, 0.017024426350851222, 0.008882309400444115, 0.010362694300518135, 0.40044411547002223, 0.01924500370096225, 0.0022205773501110288, 0.010362694300518135, 0.1236121391561806, 0.0007401924500370096, 0.0007401924500370096, 0.028127313101406367, 0.05477424130273871, 0.011102886750555145, 1.0, 0.01998519615099926, 0.0, 0.025906735751295335, 0.28275351591413767, 0.11991117690599556, 0.0007401924500370096, 0.0044411547002220575, 0.025906735751295335, 0.0, 0.0014803849000740192, 0.0, },
    { 0.2033898305084746, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.22598870056497175, 0.0, 0.0, 0.05084745762711865, 0.0, 0.0, 0.11299435028248588, 0.0, 0.0, 0.0, 0.0, 0.0, 0.005649717514124294, 0.011299435028248588, 0.0, 0.0, 0.02824858757062147, 0.0847457627118644, },
    { 0.6752450980392157, 0.3073529411764706, 0.23817401960784312, 0.17622549019607844, 0.15637254901960784, 0.22745098039215686, 0.08854166666666667, 0.4806985294117647, 0.42322303921568627, 0.02150735294117647, 0.0420343137254902, 0.13339460784313725, 0.20386029411764706, 0.16329656862745098, 0.4588235294117647, 0.21090686274509804, 0.013174019607843137, 0.12064950980392157, 0.43302696078431374, 1.0, 0.0693014705882353, 0.037806372549019605, 0.547671568627451, 0.0, 0.09816176470588235, 0.0004901960784313725, },
};

bool DEBUG_INFO = false;

static std::vector<std::string> split(std::string_view s, std::string_view delims) {
	std::vector<std::string> vec;
	size_t old_pos = 0;
	size_t pos = 0;
	std::string token;
	while((pos = s.find_first_of(delims, old_pos)) != std::string::npos) {
			token = s.substr(old_pos, pos - old_pos);
			vec.push_back(token);
			old_pos = pos + 1;
	}
	vec.push_back(std::string(s.substr(old_pos)));
	return vec;
}

struct encoding_descriptor {
	std::vector<bool> encoding;
	void push_bit(unsigned char b) {
		assert(b == (b & 1));
		encoding.push_back(b);
	}
	void pop_bit() {
		encoding.pop_back();
	}
	std::string to_string() const {
		std::string s;
		for(let const bit : encoding) {
			s += std::to_string(bit);
		}
		return s;
	}
};

class output_bitbuffer {
	std::vector<unsigned char> buffer;
	int i = 0; // byte index
	int bi = 0; // bit index
public:
	output_bitbuffer() {
		// three bit header with the number of remainder bits
		push_bit(0);
		push_bit(0);
		push_bit(0);
	};
	void push_bit(unsigned char b) {
		assert(b == (b & 1));
		assert(i <= buffer.size());
		if(i == buffer.size()) {
			buffer.push_back(0);
		}
		buffer[i] |= b << (7 - bi);
		bi++;
		if(bi == 8) {
			i++;
			bi = 0;
		}
	}
	void push_byte(unsigned char b) {
		unsigned char mask = ~((unsigned char)~0>>1);
		while(mask) {
			push_bit(b & mask ? 1 : 0);
			mask >>= 1;
		}
	}
	void push(const encoding_descriptor& descriptor) {
		for(unsigned char bit : descriptor.encoding) {
			push_bit(bit);
		}
	}
	std::vector<unsigned char>& data() {
		return buffer;
	}
	void write_header() {
		int remainder = 8 - bi;
		assert(remainder > 0);
		assert(remainder <= 9);
		remainder -= 1;
		i = 0;
		bi = 0;
		push_bit(!-!(remainder & 0x4));
		push_bit(!-!(remainder & 0x2));
		push_bit(!-!(remainder & 0x1));
	}
};

class input_bitbuffer {
	std::vector<unsigned char> buffer;
	int i = 0; // byte index
	int bi = 0; // bit index
	int remainder = 0;
public:
	input_bitbuffer(const std::vector<unsigned char>& buffer) : buffer(buffer) {
		remainder = (pop_bit() << 2)
		          | (pop_bit() << 1)
		          | pop_bit();
		remainder += 1;
	}
	unsigned char peek_bit() {
		assert(i < buffer.size());
		return (buffer[i] >> (7 - bi)) & 1;
	}
	unsigned char pop_bit() {
		unsigned char b = peek_bit();
		if(++bi == 8) {
			i++;
			bi = 0;
		}
		return b;
	}
	unsigned char pop_byte() {
		unsigned char b = 0;
		unsigned char mask = ~((unsigned char)~0>>1);
		while(mask) {
			if(pop_bit())
				b |= mask;
			mask >>= 1;
		}
		return b;
	}
	bool eof() {
		int index = 8 * i + bi;
		int size = buffer.size() * 8 - remainder;
		return index >= size;
	}
};

template<typename T>
struct tree_node {
	tree_node* left;
	tree_node* right;
	T value;
	bool is_leaf;
	int height;
	tree_node(T v, int w) : left(null), right(null), is_leaf(true), value(v), height(0) {}
	tree_node(tree_node* l, tree_node* r) :
		left(l), right(r), is_leaf(false), height(std::max(l->height, r->height) + 1) {}
	tree_node(const tree_node&) = delete;
	tree_node(tree_node&&) = delete;
	tree_node& operator=(const tree_node&) = delete;
	tree_node& operator=(tree_node&&) = delete;
	compl tree_node() {
		delete left;
		delete right;
	}
	// debugging: print the tree in graphvis format
	void print() const {
		print(false, 0, "");
	}
	// debugging: print the tree in graphvis format as a subgraph with n = the next node index
	int print(bool subgraph, int n, const std::string& label) const {
		if(subgraph) {
			printf("subgraph clusterG%d {\n", n);
			printf("\tlabel=\"%s\";\n", label.c_str());
			printf("\tcolor=invis;\n");
		} else {
			printf("graph G {\n");
		}
		printf("\tnodesep=0.3;\n");
		printf("\tranksep=0.2;\n");
		printf("\tnode [shape=circle, fixedsize=true];\n");
		printf("\tedge [arrowsize=0.8];\n");
		n = print_nodes(this, n) + 1;
		printf("}\n");
		return n;
	}
private:
	// passed the next node number
	// returns the node number left off at
	int print_nodes(const tree_node* node, int n) const {
		if(node == null) return -1;
		printf("\tn%d;\n", n);
		if(!node->is_leaf) {
			printf("\tn%d [label=\"\"];\n", n);
		} else {
			std::stringstream ss;
			ss<<node->value;
			std::string s = ss.str();
			printf("\tn%d [label=\"%s\"];\n", n, s.c_str());
		}
		int next = n + 1;
		int ret = n;
		int lnode = print_nodes(node->left, next);
		if(lnode != -1) {
			printf("\tn%d -- n%d;\n", n, next);
			ret = lnode;
			next = lnode + 1;
		} // else, next = n + 1;
		int rnode = print_nodes(node->right, next);
		if(rnode != -1) {
			printf("\tn%d -- n%d;\n", n, next);
			ret = rnode;
		}
		return ret;
	}
};

template<typename T> struct huffman_coder;

class markov_huffman {
	std::unordered_map<char, huffman_coder<char>*> map;
public:
	markov_huffman(const double(*)[26]);
	markov_huffman(const markov_huffman&) = delete;
	markov_huffman(markov_huffman&&) = delete;
	markov_huffman& operator=(const markov_huffman&) = delete;
	markov_huffman& operator=(markov_huffman&&) = delete;
	compl markov_huffman();
	encoding_descriptor encode(char, char);
	const huffman_coder<char>* get_coder(char);
};
markov_huffman generic_table(magic);

template<typename T>
struct huffman_coder {
	tree_node<T>* tree = null;
	std::unordered_map<T, encoding_descriptor> encoding_map;
	// from frequency map
	huffman_coder(const std::unordered_map<T, int>& map) {
		build_huffman_tree(map);
		build_encoding_table();
	}
	// from encoded tree
	huffman_coder(input_bitbuffer& input) {
		tree = read_dictionary(input);
		build_encoding_table(); // mainly for debugging purposes
	}
	// from hard-coded table
	huffman_coder(const double* magic) {
		std::unordered_map<char, double> map;
		for(int i = 0; i < 26; i++) {
			map.insert({ 'a' + i, magic[i] });
		}
		build_huffman_tree(map);
		build_encoding_table();
	}
	huffman_coder(const huffman_coder&) = delete;
	huffman_coder(huffman_coder&&) = delete;
	huffman_coder& operator=(const huffman_coder&) = delete;
	huffman_coder& operator=(huffman_coder&&) = delete;
	compl huffman_coder() {
		delete tree;
	}
	template<typename W>
	void build_huffman_tree(const std::unordered_map<T, W>& map) {
		std::priority_queue pq([](std::pair<W, tree_node<T>*> a, std::pair<W, tree_node<T>*> b) {
			return a.first > b.first;
		}, std::vector<std::pair<W, tree_node<T>*>>());
		for(let const& [key, count] : map) {
			pq.push({count, new tree_node<T>(key, count)});
		}
		assert(!pq.empty());
		while(pq.size() > 1) {
			let a = pq.top();
			pq.pop();
			let b = pq.top();
			pq.pop();
			if(a.second->height > b.second->height) {// purely cosmetic
				std::swap(a, b);
			}
			pq.push({a.first + b.first, new tree_node { a.second, b.second }});
		}
		tree = pq.top().second;
		pq.pop();
		assert(!tree->is_leaf); // don't want to have to deal with this rn
	}
	void build_encoding_table() {
		// Recursive builder will continuously update this descriptor while traversing the tree
		encoding_descriptor working_descriptor;
		build_encoding_table(tree, working_descriptor);
	}
	void build_encoding_table(tree_node<T>* node, encoding_descriptor& descriptor) {
		// Note: height should always be equal to the descriptor length
		if(node == null) return;
		if(!node->is_leaf) {
			descriptor.push_bit(0);
			build_encoding_table(node->left, descriptor);
			descriptor.pop_bit();
			descriptor.push_bit(1);
			build_encoding_table(node->right, descriptor);
			descriptor.pop_bit();
		} else {
			assert(encoding_map.count(node->value) == 0);
			encoding_map.insert({node->value, descriptor});
		}
	}
	encoding_descriptor encode(const T& key) {
		return encoding_map.at(key);
	}
	T decode_from_buffer(input_bitbuffer& buffer) const {
		const tree_node<T>* node = tree;
		assert(node != null);
		assert(!node->is_leaf);
		while(!node->is_leaf) {
			if(buffer.pop_bit() == 0) {
				node = node->left;
			} else {
				node = node->right;
			}
			assert(node != null);
		}
		assert(node->is_leaf);
		return node->value;
	}
	// debugging
	void print_table() {
		for(const auto& [value, encoding] : encoding_map) {
			std::cout<<"// "<<std::setw(12)<<value<<" "<<encoding.to_string()<<std::endl;
		}
	}
	unsigned read_i5(input_bitbuffer& input) {
		unsigned mask = 1 << 4;
		unsigned n = 0;
		while(mask) {
			if(input.pop_bit()) n |= mask;
			mask >>= 1;
		}
		return n;
	}
	void write_i5(unsigned n, output_bitbuffer& output) {
		assert(n < 32); // assuming no words are longer than 32 letters
		unsigned mask = 1 << 4;
		while(mask) {
			output.push_bit(!-!(n & mask));
			mask >>= 1;
		}
	}
	std::string read_string(input_bitbuffer& buffer) {
		std::string s;
		char prev = 0;
		for(int i = 0, size = read_i5(buffer); i < size; i++) {
			char c = generic_table.get_coder(prev)->decode_from_buffer(buffer);
			prev = c;
			s += c;
		}
		return s;
	}
	void write_string(std::string s, output_bitbuffer& output) {
		write_i5(s.size(), output); // length-prefixed
		char prev = 0;
		for(char c : s) {
			output.push(generic_table.encode(c, prev));
			prev = c;
		}
	}
	/*
	* Tree encoding system
	*  - Traverse the tree
	*  - If an internal node is reached, output a 0
	*  - If a leaf node is reached, output a 1 followed by the null-terminated C string
	*/
	void write_dictionary(output_bitbuffer& output) {
		static_assert(std::is_same_v<T, std::string>); // only defined for dictionary coding not character coding
		write_dictionary(tree, output);
	}
	void write_dictionary(tree_node<std::string>* node, output_bitbuffer& output) {
		if(node == null) {
			return;
		}
		if(!node->is_leaf) {
			output.push_bit(0);
		} else {
			output.push_bit(1);
			write_string(node->value, output);
		}
		if(node->left == null || node->right == null) {
			assert(node->left == null && node->right == null);
		}
		write_dictionary(node->left, output);
		write_dictionary(node->right, output);
	}
	// Reading the encoded tree is elegant
	tree_node<std::string>* read_dictionary(input_bitbuffer& buffer) {
		static_assert(std::is_same_v<T, std::string>); // only defined for dictionary coding not character coding
		if(buffer.pop_bit()) {
			return new tree_node<std::string>(read_string(buffer), 0);
		} else {
			return new tree_node<std::string>(read_dictionary(buffer), read_dictionary(buffer));
		}
	}
};

markov_huffman::markov_huffman(const double(*tables)[26]) {
	for(int i = 0; i < 26; i++) { // 0 - 25 are a - z
		let x = new huffman_coder<char>(tables[i]);
		//x->tree->print();
		//x->print_table();
		map.insert({ 'a' + i,  x});
	}
	let x = new huffman_coder<char>(tables[26]); // 26 is null
	//x->tree->print();
	//x->print_table();
	map.insert({ 0, x });
}

encoding_descriptor markov_huffman::encode(char c, char prev) {
	return map.at(prev)->encode(c);
}

const huffman_coder<char>* markov_huffman::get_coder(char prev) {
	return map.at(prev);
}

markov_huffman::compl markov_huffman() {
	for(const auto& [_, h] : map) {
		delete h;
	}
}

std::vector<unsigned char> compressText(std::string_view text) {
	std::unordered_map<std::string, int> dict;
	let words = split(text, " ");
	for(let const& word : words) {
		if(dict.count(word) == 0) {
			dict.insert({word, 1});
		} else {
			dict.at(word)++;
		}
	}
	huffman_coder<std::string> h(dict);
	if(DEBUG_INFO) {
		h.tree->print();
		h.print_table();
	}
	output_bitbuffer output;
	// write dict
	h.write_dictionary(output);
	// write content
	for(let const& word : words) {
		output.push(h.encode(word));
	}
	// fill in header
	output.write_header();
	// return
	return std::move(output.data());
}

std::string decompressText(std::vector<unsigned char>&& data) {
	input_bitbuffer buffer(std::move(data));
	huffman_coder<std::string> h(buffer);
	if(DEBUG_INFO) {
		h.tree->print();
		h.print_table();
	}
	std::string output;
	while(!buffer.eof()) {
		output += h.decode_from_buffer(buffer) + " ";
	}
	// trim end space
	assert(output.back() == ' ');
	output.pop_back();
	return output;
}





#ifdef DRIVER

std::string read_text(const std::string& path) {
	std::ifstream file(path);
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

std::vector<unsigned char> read_binary(const std::string& path) {
	std::ifstream file(path, std::ios::binary | std::ios::ate);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);
	std::vector<unsigned char> buffer(size);
	if(!file.read((char*)buffer.data(), size)) {
		assert(false);
	}
	return buffer;
}

void write_text(const std::string& path, const std::string& data) {
	std::ofstream out(path);
	out << data;
}

void write_binary(const std::string& path, const std::vector<unsigned char>& data) {
	std::ofstream out(path, std::ios::binary);
	out.write((const char*)data.data(), data.size());
}

int main(int argc, char* argv[]) {
	using namespace std::literals;
	assert(argc >= 4);
	std::string input = argv[2];
	std::string output = argv[3];
	if(argc >= 5 && argv[4] == "-t"sv) DEBUG_INFO = true;
	if(argv[1] == "-c"sv) {
		std::string text = read_text(input);
		std::vector<unsigned char> compressed = compressText(text);
		write_binary(output, compressed);
	} else if(argv[1] == "-x"sv) {
		std::vector<unsigned char> data = read_binary(input);
		std::string decompressed = decompressText(std::move(data));
		write_text(output, decompressed);
	} else {
		assert(false);
	}
}

#endif
