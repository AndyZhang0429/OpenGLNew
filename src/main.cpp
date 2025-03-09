// 头文件包含
#include"Basic.hpp"   // 基础数学和图形学相关定义
#include"Blocks.hpp"  // 方块类型定义
#include"Shader.hpp"  // 着色器管理
#include "random.hpp"  // 随机数生成
#include "Time.hpp"	  // 时间管理
#include "Properties.hpp" // 游戏属性
// 添加方块到世界
void add_block(Block* block){
	block_list.insert(std::make_pair(block->position,block));
}
unsigned getChunkpointNumber(int x,int z){
    //x+ -> 东 z+ -> 南
    //计算在16*16区块西北角的点的编号，螺旋形逆时针向外排列
    //例如：(0,0)->0,(1,0)->1,(1,1)->2,(0,1)->3,(-1,1)->4,(-1,0)->5,(-1,-1)->6,(0,-1)->7,(1,-1)->8
    //(2,0)->9,(2,1)->10,(2,2)->11,(1,2)->12,(0,2)->13,(-1,2)->14,(-2,2)->15,(-2,1)->16,(-2,0)->17,...
    int x_abs = abs(x),z_abs = abs(z);
    int max_abs = std::max(x_abs,z_abs)*2-1; // 里圈的边长
    int max_abs_outer = std::max(x_abs,z_abs)*2+1; // 外圈的边长
    int step = std::max(x_abs,z_abs)*2; // 每圈的边长
    int max_abs_inner_square = max_abs*max_abs; // 里圈的面积
    int point_count_on_this_round = max_abs<<2+4; // 本圈的点的数量
    //这个点在本圈的正方形的序号（从0开始）
    unsigned num = (
        (z==step/2)?x-step/2+step:
        (x==-step/2)?z+step/2+2*step:
        (z==-step/2)?x+step/2+3*step:
        (x==step/2)?z-step/2+0*step:
        0
    );//这个点在本圈的序号（从0开始）
    return max_abs_inner_square+num;//返回这个点的编号
}
void genChunk(int x,int z){// 生成一个区块（16*16）顶点的编号螺旋形逆时针向外排列
    int pointnumbers[4] = {
        getChunkpointNumber(x,z),//左上角
        getChunkpointNumber(x,z+1),//右上角
        getChunkpointNumber(x+1,z+1),//右下角
        getChunkpointNumber(x+1,z),//左下角
    };//四个顶点的编号
    unsigned long long randoms[4]{
        Random::getrandbytimes(pointnumbers[0]),
        Random::getrandbytimes(pointnumbers[1]),
        Random::getrandbytimes(pointnumbers[2]),
        Random::getrandbytimes(pointnumbers[3]),
    };//四个顶点的随机数 （为[空],高度原值,梯度原值(8bits*2)）
    //通过随机数用柏林噪声生成方块
    int leftx = x*16;
    int leftz = z*16;
    int rightx = leftx+16;
    int rightz = leftz+16;
    // 获取四个角的高度和梯度
    int height00 = randoms[0]>>16&0xff;
    Point gradient00 = Point((char)(randoms[0]&0xff00>>8),(char)(randoms[0]&0xff)).normalize();
    int height01 = randoms[1]>>16&0xff;
    Point gradient01 = Point((char)(randoms[1]&0xff00>>8),(char)(randoms[1]&0xff)).normalize();
    int height11 = randoms[2]>>16&0xff;
    Point gradient11 = Point((char)(randoms[2]&0xff00>>8),(char)(randoms[2]&0xff)).normalize();
    int height10 = randoms[3]>>16&0xff;
    Point gradient10 = Point((char)(randoms[3]&0xff00>>8),(char)(randoms[3]&0xff)).normalize();
    
    for(int _x = 0;_x < 16;_x++)
        for(int _z = 0;_z < 16;_z++){
            Vec3 pos = Vec3(x*16+_x,0,z*16+_z);
            // 计算当前点在区块内的相对位置（0到1之间）
            double u = static_cast<double>(_x) / 16.0;
            double v = static_cast<double>(_z) / 16.0;
            
            // 计算四个角的权重
            double dot00 = (gradient00.x * u + gradient00.y * v)*height00;
            double dot01 = (gradient01.x * u + gradient01.y * (1 - v))*height01;
            double dot11 = (gradient11.x * (1 - u) + gradient11.y * (1 - v))*height11;
            double dot10 = (gradient10.x * (1 - u) + gradient10.y * v)*height10;
            
            // 使用平滑插值函数
            double fadeU0 = fade(dot00, dot10, u);
            double fadeU1 = fade(dot01, dot11, u);
            double height = fade(fadeU0, fadeU1, v);
            // std::cout<<height<<std::endl;
            // 将高度值限制在合理范围内
            height = std::max(0.0, std::min(height*(1.0/32.0)+60, 255.0));
            // 根据高度生成方块
            for(int y = 0; y < height-3; y++) {
                Vec3 blockPos = Vec3(pos.first, y, pos.third);
                add_block(new Stone(blockPos));
            }
            for(int y = height-3; y < height-1; y++) {
                Vec3 blockPos = Vec3(pos.first, y, pos.third);
                add_block(new Soil(blockPos));
            }
            for(int y = height-1; y < height; y++) {
                Vec3 blockPos = Vec3(pos.first, y, pos.third);
                add_block(new Grass(blockPos));
            }
        }

}
// 检查方块可见性
void check_show(Block* block) {
    if(!block) return;  // 添加空指针检查
    Vec3 block_pos = block->position;
    unsigned char face_mask = 0;
    
    // Check each direction and set corresponding bit
    if(!block_list.count(block_pos+Vector3::up))    face_mask |= 0x08; // y+
    if(!block_list.count(block_pos-Vector3::up))    face_mask |= 0x04; // y-
    if(!block_list.count(block_pos+Vector3::right))  face_mask |= 0x20; // x+
    if(!block_list.count(block_pos-Vector3::right))  face_mask |= 0x10; // x-
    if(!block_list.count(block_pos-Vector3::front)) face_mask |= 0x02; // z+
    if(!block_list.count(block_pos+Vector3::front)) face_mask |= 0x01; // z-
    
    // Set visible faces based on the mask
    block->set_show(face_mask);
    
    // Add block to display list if any faces are visible
    if(face_mask != 0) {
        toDisplay.insert(block);
    } else {
        toDisplay.erase(block);
    }
	block->refreshBuffer();
}
// 检查屏幕中心所指向的方块
void getTargetBlock(Block*& toBreak,Vec3& toPut) {
    // 计算射线方向
    glm::vec3 rayDir = glm::vec3(
        std::cos(pitch*toRad)*std::sin(yaw*toRad),
        std::sin(pitch*toRad),
        std::cos(pitch*toRad)*std::cos(yaw*toRad)
    );
    
    // 射线起点（摄像机位置）
    glm::vec3 rayStart = glm::vec3(x, y, z);
    
    // 最大检测距离
    float maxDistance = 5.0f;
    
    // 当前检测位置
    glm::vec3 currentPos = rayStart;
    // 上一个方块坐标
    Vec3 lastBlockPos = Vec3(
        static_cast<int>(std::floor(currentPos.x)),
        static_cast<int>(std::floor(currentPos.y)),
        static_cast<int>(std::floor(currentPos.z))
    );
    
    while(true) {
        // 计算当前方块坐标
        Vec3 blockPos = Vec3(
            static_cast<int>(std::floor(currentPos.x)),
            static_cast<int>(std::floor(currentPos.y)),
            static_cast<int>(std::floor(currentPos.z))
        );
        
        // 计算到起点的距离
        float distance = glm::length(currentPos - rayStart);
        if(distance > maxDistance) {
            break;
        }
        
        // 如果方块坐标改变
        if(blockPos != lastBlockPos) {
            // 检查该位置是否有方块
            if(block_list.count(blockPos)) {
            	toPut = lastBlockPos;
                toBreak = block_list[blockPos];
                return;
            }
            lastBlockPos = blockPos;
        }
        
        
        // 计算下一步的位置
        // 找到下一个可能改变方块坐标的最小步长
        float tMin = std::numeric_limits<float>::max();
        if(rayDir.x != 0) {
            float tx = (blockPos.first + (rayDir.x > 0 ? 1 : 0) - currentPos.x) / rayDir.x;
            tMin = std::min(tMin, tx);
        }
        if(rayDir.y != 0) {
            float ty = (blockPos.second + (rayDir.y > 0 ? 1 : 0) - currentPos.y) / rayDir.y;
            tMin = std::min(tMin, ty);
        }
        if(rayDir.z != 0) {
            float tz = (blockPos.third + (rayDir.z > 0 ? 1 : 0) - currentPos.z) / rayDir.z;
            tMin = std::min(tMin, tz);
        }
        tMin = tMin==0?0.0001f:tMin; 
        // 更新当前位置
        currentPos += rayDir * tMin;
    }
    
    return ;  // 没有找到方块
}


// 画一个以左下角为给定点的大小为1的线框立方体
void drawSelectionCube(double x, double y, double z) {
    // GLboolean depthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
    // if(depthTestEnabled) glDisable(GL_DEPTH_TEST);

    glUseProgram(Line_loop_shader);
    glLineWidth(2.0f);
    GLint modelLoc = glGetUniformLocation(Block_shader, "model");
    GLint viewLoc = glGetUniformLocation(Block_shader, "view");
    GLint projLoc = glGetUniformLocation(Block_shader, "projection");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));
    
    // 定义立方体的线框顶点
    float vertices[] = {
        // 前面
        x, y, z,
        x+1, y, z,
        x+1, y+1, z,
        x, y+1, z,
        // 后面
        x, y, z+1,
        x+1, y, z+1,
        x+1, y+1, z+1,
        x, y+1, z+1,
        // 连接前后面的线
        x, y, z,
        x, y, z+1,
        x+1, y, z,
        x+1, y, z+1,
        x+1, y+1, z,
        x+1, y+1, z+1,
        x, y+1, z,
        x, y+1, z+1
    };
    
    // 创建并绑定VBO
    GLuint VBO, VAO;

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    // 绑定并填充顶点数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // 绘制线框
    glDrawArrays(GL_LINE_LOOP, 0, 4); // 前面
    glDrawArrays(GL_LINE_LOOP, 4, 4); // 后面
    glDrawArrays(GL_LINES, 8, 8);    // 连接前后面的线
    
    // 清理
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    // if(depthTestEnabled) glEnable(GL_DEPTH_TEST);
}

// 初始化OpenGL
void initOpenGL() {
    Block_shader = createShaderProgram(readfile("../shaders/vertex_shader_of_blocks.glsl").c_str(), 
                                       readfile("../shaders/fragment_shader_of_blocks.glsl").c_str());
    Line_loop_shader = createShaderProgram(readfile("../shaders/vertex_shader_of_lines.glsl").c_str(),
                                           readfile("../shaders/fragment_shader_of_lines.glsl").c_str());
    UI_shader = createShaderProgram(readfile("../shaders/vertex_shader_of_UI.glsl").c_str(),
                                           readfile("../shaders/fragment_shader_of_UI.glsl").c_str());
	glGenVertexArrays(1, &VAO);
}
void initUI(){
    UIs["pointer"]=texture("UI/aim_cross");
    UIs["pointer"].load();
}
Vec4 getPlaceofUI(String name){
    if(name=="pointer"){
        // 修正坐标计算，转换为屏幕中心对齐
        double size = 64;
        return Vec4(
            -size/2/WIDTH_OF_WINDOW,  // 左
            -size/2/HEIGHT_OF_WINDOW, // 上 
            size/2/WIDTH_OF_WINDOW,  // 右
            size/2/HEIGHT_OF_WINDOW // 下
        );
    }else{
        return Vec4(0,0,0,0);
    }
}
// 游戏初始化
void init(){
    Random::srand(seed);
    for(int _x = -2;_x < 2;_x++)
    for(int _z = -2;_z < 2;_z++)
    genChunk(_x,_z);
	for(std::pair<Vec3,Block*>block: block_list){
		check_show(block.second);
	}
	initOpenGL();
    initUI();
	std::cout<<"Initialize_Done!"<<std::endl;
}

// 游戏结束清理
void finish(){
	for(std::pair<Vec3,Block*>block: block_list){
		delete block.second;
	}
	block_list.clear();
	
	glDeleteVertexArrays(1, &VAO);
	
	
    wglDeleteContext(winRC);
    ReleaseDC(winND, winDC);
}

// 角度限制
void clamp(){
    //误差
    double error = 0.001;
    if(pitch>90-error)pitch=90-error;
    if(pitch<-90+error)pitch=-90+error;
	if(yaw>=360)yaw-=360;
	if(yaw<0)yaw+=360;
}

// 游戏主循环
void manageKeys(){
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
        exit(0);
    }
    
    
    double dT=display_timer.deltaTime();
    //manage tick
	time_since_last_tick += dT;
	if(time_since_last_tick>=0.05){
        std::cout<<"tick"<<tick;
        std::cout<<":"<<std::endl;
        for(unsigned event:events_happened_in_tick){
        	std::cout<<event<<std::endl;
		}
		events_happened_in_tick.clear(); 
		while(time_since_last_tick>=0.05){
			time_since_last_tick-=0.05; 
			tick++;
		}
        
	}
	//end//
    
    RECT window_rect;
    GetWindowRect(winND, &window_rect);
    int CenterX = (window_rect.right + window_rect.left)/2;
    int CenterY = (window_rect.top + window_rect.bottom)/2;
    WIDTH_OF_WINDOW = window_rect.right - window_rect.left;
    HEIGHT_OF_WINDOW = window_rect.bottom - window_rect.top;
    glViewport(0,0,WIDTH_OF_WINDOW,HEIGHT_OF_WINDOW);
    
    // Handle mouse input for camera rotation
    POINT pt = getcursor(winND);
    pt.x-=CenterX;
    pt.y-=CenterY;
    SetCursorPos(CenterX,CenterY);
    yaw-=pt.x*sensitivity_mouse;
    pitch-=pt.y*sensitivity_mouse;
    clamp();  
	// Handle keyboard input for movement
    if (GetAsyncKeyState('W') & 0x8000) {
        if(GetAsyncKeyState(VK_LCONTROL)){
            x+=std::sin(yaw*toRad)*speed_sprint*dT;
            z+=std::cos(yaw*toRad)*speed_sprint*dT;
        }else{
            x+=std::sin(yaw*toRad)*speed*dT;
            z+=std::cos(yaw*toRad)*speed*dT;
        }
    }
    if (GetAsyncKeyState('S') & 0x8000) {
        x-=std::sin(yaw*toRad)*speed*dT;
        z-=std::cos(yaw*toRad)*speed*dT;
    }
    if (GetAsyncKeyState('A') & 0x8000) {
        x+=std::sin((yaw+90)*toRad)*speed*dT;
        z+=std::cos((yaw+90)*toRad)*speed*dT;
    }
    if (GetAsyncKeyState('D') & 0x8000) {
        x+=std::sin((yaw-90)*toRad)*speed*dT;
        z+=std::cos((yaw-90)*toRad)*speed*dT;
    }
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        y+=speed*dT;
    }
    if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) {
        y-=speed*dT;
    }//处理移动
}
void DrawUI(){
    GLboolean depthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
    if(depthTestEnabled) glDisable(GL_DEPTH_TEST);
    for(std::pair<String,texture>UI:UIs){
        Vec4 place = getPlaceofUI(UI.first);
        glUseProgram(UI_shader);
        float buffer[]={
            // 修正为：左下 -> 左上 -> 右上 -> 右下（纹理坐标需要翻转Y轴）
            place.first,  place.fourth, 0.0f, 1.0f,  // 左下 (纹理坐标y=1)
            place.first,  place.second, 0.0f, 0.0f,   // 左上 (纹理坐标y=0)
            place.third,  place.second, 1.0f, 0.0f,   // 右上
            place.third,  place.fourth, 1.0f, 1.0f    // 右下
        };
        GLuint _VBO, _VAO;
        glGenBuffers(1, &_VBO);
        glGenVertexArrays(1, &_VAO);
        glBindVertexArray(_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,UI.second.sequal);
        glUniform1i(glGetUniformLocation(UI_shader, "tex"), 0);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glDeleteBuffers(1, &_VBO);
        glDeleteVertexArrays(1, &_VAO);
    }
   
    if(depthTestEnabled) glEnable(GL_DEPTH_TEST);
}

void game(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    modelMat = glm::mat4(1.0f); 
    viewMat = glm::lookAt(glm::vec3(x, y, z), 
								 glm::vec3(x+std::cos(pitch*toRad)*std::sin(yaw*toRad),y+std::sin(pitch*toRad),z+std::cos(pitch*toRad)*std::cos(yaw*toRad)),
								 glm::vec3(0.0f,1.0f,0.0f));
    projectionMat = glm::perspective((float)glm::radians(fov), (float)WIDTH_OF_WINDOW / HEIGHT_OF_WINDOW, 0.1f, 300.0f);
	
    // Draw selection cube if a block is targeted
    Block* targetB = nullptr;
    Vec3 targetP(0,-65536,0);
	getTargetBlock(targetB,targetP);
    // std::cout<<target<<std::endl;
    if(targetB!=nullptr){
        drawSelectionCube(targetB->position.first,targetB->position.second,targetB->position.third);
    }
	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000)&&
	(!(events_happened_in_tick.count(player<<16|BREAK_BLOCK)))&&
	(!(events_happened_in_tick.count(player<<16|PUT_BLOCK)))&&
	targetB!=nullptr
	) {
		events_happened_in_tick.insert(player<<16|BREAK_BLOCK);
		// 保存目标方块位置
		Vec3 pos = targetB->position;
		delete targetB;
		// 从显示集合中移除方块
		toDisplay.erase(targetB);
		
		// 从方块列表中移除并删除方块
		block_list.erase(targetB->position);
		targetB = nullptr;  // 将target置为nullptr
		Vec3 blocks_to_update[6]={
			Vec3(0,0,1),
			Vec3(0,0,-1),
			Vec3(1,0,0),
			Vec3(-1,0,0),
			Vec3(0,1,0),
			Vec3(0,-1,0),
		};
		// 更新周围方块的可见性
		for(Vec3 block_to_update:blocks_to_update){
			Vec3 neighborPos = pos + block_to_update;
//          std::cout<<neighborPos.first<< neighborPos.second << neighborPos.third <<std::endl;
			if(block_list.count(neighborPos)) {
				std::cout<<neighborPos.first<< neighborPos.second << neighborPos.third <<std::endl;
				check_show(block_list[neighborPos]);
			}
		}
	}
	
//	std::cout<<targetP.first <<","<< targetP.second  <<","<< targetP.third <<std::endl;
	
	if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000)&&
	(!(events_happened_in_tick.count(player<<16|BREAK_BLOCK)))&&
	(!(events_happened_in_tick.count(player<<16|PUT_BLOCK)))&&
	targetP!=Vec3(0,-65536,0)&&
	block_list.count(targetP)==0
	) {
		events_happened_in_tick.insert(player<<16|PUT_BLOCK);
		block_list[targetP]=new Stone(targetP);
		Vec3 blocks_to_update[7]={
			Vec3(0,0,1),
			Vec3(0,0,-1),
			Vec3(1,0,0),
			Vec3(-1,0,0),
			Vec3(0,1,0),
			Vec3(0,-1,0),
			Vec3(0,0,0),
		};
		// 更新周围方块的可见性
		for(Vec3 block_to_update:blocks_to_update){
			Vec3 neighborPos = targetP + block_to_update;
//          std::cout<<neighborPos.first<< neighborPos.second << neighborPos.third <<std::endl;
			if(block_list.count(neighborPos)) {
				std::cout<<neighborPos.first<< neighborPos.second << neighborPos.third <<std::endl;
				check_show(block_list[neighborPos]);
			}
		}
	}
    // Clear screen and set up OpenGL rendering
    glUseProgram(Block_shader);
    
    // Get uniform locations for transformation matrices
    GLint modelLoc = glGetUniformLocation(Block_shader, "model");
    GLint viewLoc = glGetUniformLocation(Block_shader, "view");
    GLint projLoc = glGetUniformLocation(Block_shader, "projection");
    
    // Create transformation matrices
    
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));
    
    // Render all visible blocks
    for(Block *block:toDisplay){
        Vec3 pos = block->position;
        std::map<String,texture> textures = block->getTextures();
        
        // Render each visible face of the block
        for(String face : block->faces_to_show){
            textures[face].load();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textures[face].sequal);
            glUniform1i(glGetUniformLocation(Block_shader, "tex"), 0);
            glBindBuffer(GL_ARRAY_BUFFER, block->buffers[face]);
            glBindVertexArray(VAO);
            
            // Set up vertex attributes
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
            glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(5 * sizeof(float)));
            
            // Enable vertex attributes and draw
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        }
    }
    
    DrawUI();
    // Swap buffers to display rendered frame
    SwapBuffers(winDC);
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

// 程序入口
int main(int _argc,char ** _argv){
	freopen(".log","w",stdout);
	display_timer.init();
	
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProcedure;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = "MyWindowClass";
	RegisterClass(&wc);
	winND = CreateWindow(
	    "MyWindowClass",       // 窗口类名
	    WINDOW_NAME,           // 窗口标题
	    WS_OVERLAPPEDWINDOW,   // 窗口样式
	    CW_USEDEFAULT,         // 初始x位置
	    CW_USEDEFAULT,         // 初始y位置
	    WIDTH_OF_WINDOW,         // 初始宽度
	    HEIGHT_OF_WINDOW,         // 初始高度
	    NULL,                  // 父窗口句柄
	    NULL,                  // 无菜单句柄
	    GetModuleHandle(NULL), // 应用程序实例句柄
	    NULL                   // 无窗口创建数据
	);
	init_window(winND,winRC,winDC);
	
	ShowWindow(winND, SW_SHOW);
	UpdateWindow(winND);
	
	
    wglMakeCurrent(winDC, winRC);
	
    ShowCursor(FALSE);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
	glClearColor(0.625,0.875,1,0);
	
	glewInit();
	init();
	
	LPMSG msg = {};
	while(1){
		if(PeekMessage(msg,winND,0,0,1)){
		    TranslateMessage(msg);
		    DispatchMessage(msg);
		}
		manageKeys();
		game();
    	getERR();
	}
	
    wglMakeCurrent(NULL, NULL);
	finish();
	return 0;
}

