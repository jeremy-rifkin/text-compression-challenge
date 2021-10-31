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

constexpr double magic[27][27] = {
    { 0.001665001665001665, 0.1496836496836497, 0.2524142524142524, 0.36413586413586413, 0.0028305028305028305, 0.037462537462537464, 0.13936063936063936, 0.003663003663003663, 0.25607725607725607, 0.0018315018315018315, 0.09174159174159174, 0.5198135198135199, 0.12337662337662338, 1.0, 0.0014985014985014985, 0.14402264402264403, 0.0004995004995004995, 0.6082251082251082, 0.7352647352647352, 0.7713952713952714, 0.05194805194805195, 0.11655011655011654, 0.045454545454545456, 0.00333000333000333, 0.15434565434565434, 0.008824508824508824, 0.485014985014985, },
    { 0.17753067484662577, 0.03872699386503067, 0.0007668711656441718, 0.0011503067484662577, 1.0, 0.0, 0.0, 0.0003834355828220859, 0.11042944785276074, 0.020322085889570553, 0.0, 0.40299079754601225, 0.005751533742331288, 0.0003834355828220859, 0.31901840490797545, 0.0, 0.0, 0.24348159509202455, 0.03834355828220859, 0.012653374233128834, 0.325920245398773, 0.009969325153374233, 0.0, 0.0, 0.18059815950920247, 0.0, 0.037960122699386506, },
    { 0.5969026548672567, 0.0, 0.084070796460177, 0.0008849557522123894, 0.9252212389380531, 0.0, 0.0, 0.765929203539823, 0.24513274336283186, 0.0, 0.32212389380530976, 0.16858407079646018, 0.0, 0.0, 1.0, 0.0, 0.002654867256637168, 0.2721238938053097, 0.010176991150442478, 0.4411504424778761, 0.16106194690265488, 0.0, 0.0, 0.0, 0.02654867256637168, 0.0, 0.11150442477876106, },
    { 0.040551981036234336, 0.001015916017609211, 0.0008465966813410091, 0.01938706400270911, 0.17905519810362344, 0.002031832035218422, 0.006603454114459871, 0.0019471723670843211, 0.11649170335252286, 0.0012698950220115138, 0.0, 0.019133084998306807, 0.002116491703352523, 0.005418218760582459, 0.0841517101252963, 0.0003386386725364037, 0.0, 0.027260413139180494, 0.05088046054859465, 0.0024551303758889266, 0.021503555706061633, 0.0024551303758889266, 0.0017778530308161192, 0.0, 0.021757534710463936, 0.0, 1.0, },
    { 0.13820673900628214, 0.0034742052160670095, 0.058490386445840474, 0.2334380354083381, 0.10184656386826575, 0.02460498762611841, 0.0105653912050257, 0.005853797829811536, 0.026889396535313154, 0.0003807348181991243, 0.003807348181991243, 0.09347039786788502, 0.06848467542356748, 0.24633542737483344, 0.010850942318675044, 0.02560441652389111, 0.0037597563297163527, 0.3606034646868456, 0.1739958119169998, 0.07371977917380544, 0.005092328193413287, 0.06382067390062822, 0.02555682467161622, 0.029792499524081476, 0.04288025889967637, 0.0008566533409480297, 1.0, },
    { 0.1619297826606162, 0.0009553379508000956, 0.004060186290900406, 0.0019106759016001911, 0.2130403630284213, 0.11153570575591115, 0.0, 0.0011941724385001193, 0.18366372104131837, 0.0, 0.0, 0.07188918079770719, 0.0, 0.0004776689754000478, 0.3436828278003344, 0.0009553379508000956, 0.0, 0.17411034153331742, 0.004776689754000477, 0.07045617387150704, 0.0790542154287079, 0.0, 0.0002388344877000239, 0.0, 0.0059708621925005975, 0.0, 1.0, },
    { 0.1680178920883422, 0.0008386916410399776, 0.0, 0.0022365110427732737, 0.3296058149287112, 0.0, 0.03131115459882583, 0.35951915012580377, 0.13279284316466314, 0.0, 0.0, 0.07045009784735812, 0.0061504053676265024, 0.034665921162985745, 0.13670673748951637, 0.005311713726586525, 0.0, 0.13614760972882303, 0.06625663964215824, 0.01453732177802628, 0.08079396142018451, 0.0, 0.0, 0.0, 0.01034386357282639, 0.0002795638803466592, 1.0, },
    { 0.3705921004599547, 0.0006570781923048843, 0.0004380521282032562, 0.00014601737606775207, 1.0, 0.0012411476965758926, 7.300868803387604e-05, 0.00014601737606775207, 0.29678031685770606, 0.0, 0.0, 0.0018252172008469008, 0.0013141563846097686, 0.0017522085128130248, 0.13754836825582245, 0.0002190260641016281, 7.300868803387604e-05, 0.023289771482806455, 0.0038694604657954295, 0.06322552383733664, 0.020880484777688543, 0.0, 0.0005840695042710083, 0.0, 0.012922537781996058, 0.0, 0.18960356282397606, },
    { 0.06850020601565719, 0.03069633292130202, 0.188504326328801, 0.13988463123197362, 0.11454470539761022, 0.07354758961681088, 0.09404614750721055, 0.0008240626287597857, 0.000927070457354759, 0.0, 0.02976926246394726, 0.1361763494025546, 0.17140502678203542, 1.0, 0.14400494437577255, 0.024927894519983517, 0.001854140914709518, 0.10249278945199836, 0.3479604449938195, 0.4787803873094355, 0.002266172229089411, 0.0645859085290482, 0.0, 0.008446641944787803, 0.0, 0.018438401318500205, 0.04233621755253399, },
    { 0.088, 0.0, 0.0, 0.0, 0.404, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.336, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.004, },
    { 0.03697183098591549, 0.016725352112676055, 0.007922535211267605, 0.0008802816901408451, 0.9779929577464789, 0.0035211267605633804, 0.0044014084507042256, 0.007922535211267605, 0.4727112676056338, 0.0, 0.0, 0.05369718309859155, 0.006161971830985915, 0.37411971830985913, 0.0017605633802816902, 0.006161971830985915, 0.0017605633802816902, 0.002640845070422535, 0.12235915492957747, 0.0, 0.017605633802816902, 0.0, 0.032570422535211266, 0.0, 0.022887323943661973, 0.0, 1.0, },
    { 0.4166666666666667, 0.005997474747474747, 0.008207070707070708, 0.48169191919191917, 1.0, 0.11142676767676768, 0.0022095959595959595, 0.0003156565656565657, 0.7152777777777778, 0.0003156565656565657, 0.03819444444444445, 0.7679924242424242, 0.052398989898989896, 0.0022095959595959595, 0.41792929292929293, 0.022095959595959596, 0.0003156565656565657, 0.023674242424242424, 0.13415404040404041, 0.11900252525252525, 0.10132575757575757, 0.028724747474747476, 0.049873737373737376, 0.0, 0.6202651515151515, 0.0, 0.7575757575757576, },
    { 0.44065142499217036, 0.11337300344503602, 0.0015659254619480112, 0.00031318509238960227, 1.0, 0.004697776385844034, 0.0, 0.0, 0.3225806451612903, 0.00031318509238960227, 0.0, 0.0028186658315064203, 0.06451612903225806, 0.008769182586908864, 0.38740995928593797, 0.20012527403695585, 0.0, 0.021609771374882555, 0.08894456623864704, 0.0018791105543376136, 0.11368618853742563, 0.0, 0.0006263701847792045, 0.0, 0.04854368932038835, 0.0, 0.5646727215784528, },
    { 0.06480083613982116, 0.002438741145047033, 0.11253048426431309, 0.4991290210196261, 0.3439786319823482, 0.016606665892463127, 0.5031935895947044, 0.002438741145047033, 0.11566600859365928, 0.0013935663685983046, 0.03623272558355592, 0.04169086052723261, 0.004064568575078388, 0.026013238880501683, 0.27348739983741727, 0.0020903495528974566, 0.005109743351527116, 0.001858088491464406, 0.20636395308326558, 0.3505980722331901, 0.027522935779816515, 0.014400185808849147, 0.0032516548600627104, 0.0008129137150156776, 0.05225873882243642, 0.0005806526535826269, 1.0, },
    { 0.028278132868487314, 0.08367228355607205, 0.09819872167344568, 0.11408096068177416, 0.014913809800503584, 0.7197365872554716, 0.04474142940151075, 0.003873716831299632, 0.06682161533991865, 0.000968429207824908, 0.08270385434824715, 0.2285492930466783, 0.38582219639744336, 1.0, 0.22506294789850861, 0.12415262444315321, 0.0, 0.7420104590354445, 0.18768158047646716, 0.3933759442184776, 0.9943831105946155, 0.12124733681967848, 0.3083478597714507, 0.009103234553554135, 0.01820646910710827, 0.004067402672864613, 0.7749370521014913, },
    { 0.7300832342449465, 0.0005945303210463733, 0.0, 0.0, 1.0, 0.0023781212841854932, 0.0, 0.10523186682520809, 0.2740784780023781, 0.0, 0.0, 0.4702734839476813, 0.0047562425683709865, 0.010107015457788348, 0.5891795481569561, 0.3501783590963139, 0.0, 0.5695600475624257, 0.12663495838287753, 0.20154577883472058, 0.18370986920332938, 0.0, 0.0017835909631391202, 0.0, 0.028537455410225922, 0.0, 0.4583828775267539, },
    { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, },
    { 0.24676125848241826, 0.007094386181369525, 0.029765576804441703, 0.1135101789019124, 1.0, 0.015885256014805674, 0.03485502776064158, 0.02313386798272671, 0.3258790869833436, 0.0, 0.04426280074028378, 0.05351634793337446, 0.06153608883405305, 0.06523750771128933, 0.35502776064157926, 0.014805675508945095, 0.00015422578655151142, 0.07449105490438002, 0.20635410240592228, 0.20882171499074645, 0.08281924737816163, 0.015885256014805674, 0.011721159777914868, 0.00015422578655151142, 0.16455891425046268, 0.0, 0.8632017273288094, },
    { 0.09495770442859512, 0.000829324929507381, 0.03897827168684691, 0.0009951899154088573, 0.22466412340354952, 0.003400232210980262, 0.0015757173660640238, 0.11071487808923536, 0.13584342345330902, 0.0, 0.009454304196384144, 0.028528777575053905, 0.021645380660142644, 0.008210316802123072, 0.11477857024382153, 0.05456958036158567, 0.0031514347321280477, 0.0004146624647536905, 0.11544203018742744, 0.34408691325261237, 0.06219936971305357, 0.0, 0.013186266379167358, 0.0, 0.012274008956709239, 0.0, 1.0, },
    { 0.0980215203054495, 0.0011801457827143353, 0.011246095105866018, 0.0006247830614370011, 0.25484206872613674, 0.0016660881638320027, 0.00020826102047900034, 1.0, 0.19514057618882333, 0.0, 0.0, 0.036376258243665395, 0.00388753904894134, 0.0014578271433530025, 0.28934397778549115, 0.0007636237417563346, 0.0, 0.09413398125650815, 0.06289482818465811, 0.05206525511975009, 0.048247136410968415, 0.0, 0.02457480041652204, 0.0, 0.06386671294689344, 0.0, 0.7995140576188823, },
    { 0.2034313725490196, 0.13088235294117648, 0.22303921568627452, 0.09607843137254903, 0.19117647058823528, 0.031862745098039214, 0.39950980392156865, 0.0, 0.12794117647058822, 0.0, 0.0, 0.8073529411764706, 0.17598039215686276, 0.6323529411764706, 0.021568627450980392, 0.29411764705882354, 0.0, 0.8588235294117647, 0.6818627450980392, 1.0, 0.0, 0.007352941176470588, 0.0, 0.00392156862745098, 0.0058823529411764705, 0.0029411764705882353, 0.4769607843137255, },
    { 0.0952836201402167, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.1701720841300191, 0.0, 0.0, 0.0, 0.0, 0.00031867431485022306, 0.09273422562141491, 0.0, 0.0, 0.0009560229445506692, 0.0, 0.0, 0.0012746972594008922, 0.0, 0.0, 0.0, 0.011153601019757807, 0.0, 0.0006373486297004461, },
    { 1.0, 0.0, 0.0005765350245027386, 0.011242432977803401, 0.476217930239262, 0.0008648025367541078, 0.0, 0.5615451138656673, 0.5756702219659844, 0.0, 0.0017296050735082155, 0.016431248198328047, 0.0002882675122513693, 0.13000864802536755, 0.35802825021620066, 0.0011530700490054772, 0.0, 0.050446814643989625, 0.04900547708273278, 0.0017296050735082155, 0.0005765350245027386, 0.0, 0.0008648025367541078, 0.0, 0.002017872585759585, 0.0, 0.2868261746901124, },
    { 0.5540540540540541, 0.0, 0.7162162162162162, 0.0, 0.3716216216216216, 0.006756756756756757, 0.0, 0.06756756756756757, 1.0, 0.0, 0.0, 0.006756756756756757, 0.0, 0.0, 0.006756756756756757, 0.7635135135135135, 0.006756756756756757, 0.0, 0.006756756756756757, 0.9256756756756757, 0.14864864864864866, 0.0, 0.02702702702702703, 0.0, 0.10810810810810811, 0.0, 0.6283783783783784, },
    { 0.005121042830540037, 0.003569211669770329, 0.00186219739292365, 0.0021725636250775914, 0.08395406579764121, 0.0040347610180012415, 0.0004655493482309125, 0.0021725636250775914, 0.02591558038485413, 0.00015518311607697082, 0.00015518311607697082, 0.005896958410924891, 0.011483550589695841, 0.0023277467411545625, 0.20965238981998757, 0.004189944134078212, 0.0, 0.005431409062693979, 0.059279950341402855, 0.025139664804469275, 0.00015518311607697082, 0.000931098696461825, 0.005431409062693979, 0.0, 0.00031036623215394165, 0.0, 1.0, },
    { 0.2033898305084746, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.22598870056497175, 0.0, 0.0, 0.05084745762711865, 0.0, 0.0, 0.11299435028248588, 0.0, 0.0, 0.0, 0.0, 0.0, 0.005649717514124294, 0.011299435028248588, 0.0, 0.0, 0.02824858757062147, 0.0847457627118644, 0.005649717514124294, },
    { 0.6752450980392157, 0.3073529411764706, 0.23817401960784312, 0.17622549019607844, 0.15637254901960784, 0.22745098039215686, 0.08854166666666667, 0.4806985294117647, 0.42322303921568627, 0.02150735294117647, 0.0420343137254902, 0.13339460784313725, 0.20386029411764706, 0.16329656862745098, 0.4588235294117647, 0.21090686274509804, 0.013174019607843137, 0.12064950980392157, 0.43302696078431374, 1.0, 0.0693014705882353, 0.037806372549019605, 0.547671568627451, 0.0, 0.09816176470588235, 0.0004901960784313725, 6.127450980392157e-05, },
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
			std::string s = node->value;
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
	markov_huffman(const double(*)[27]);
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
		map.insert({ 0, magic[26] });
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
	std::string read_string(input_bitbuffer& buffer) {
		std::string s;
		char prev = 0;
		while(true) {
			char c = generic_table.get_coder(prev)->decode_from_buffer(buffer);
			prev = c;
			if(c == 0) break;
			s += c;
		}
		return s;
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
			char prev = 0;
			for(char c : node->value) {
				output.push(generic_table.encode(c, prev));
				prev = c;
			}
			output.push(generic_table.encode(0, prev)); // null terminator
		}
		if(node->left == null || node->right == null)
			assert(node->left == null && node->right == null);
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

markov_huffman::markov_huffman(const double(*tables)[27]) {
	for(int i = 0; i < 26; i++) {
		map.insert({ 'a' + i, new huffman_coder<char>(tables[i]) });
	}
	map.insert({ 0, new huffman_coder<char>(tables[26]) });
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
