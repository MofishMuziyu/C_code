typedef struct Quadnode{
	//四个子树的指针
	struct Quadnode *left_up, *right_up, *left_down, *right_down;
	
	//color
	color ** colors;

	int width, height;
	int pos_x, pos_y;
	int  valid;

	//color mean rgb color
	int mean_r,mean_g,mean_b;
	long long sigma_r,sigma_g,sigma_b;
};


void init_quadnode(struct Quadnode * root){
	root->left_up = NULL;
	root->right_up = NULL;
	root->left_down = NULL;
	root->right_down = NULL;
	root->width = 0;
	root->height = 0;
	root->pos_x = 0;
	root->pos_y = 0;

	root->valid = 0;
	root->mean_r = root->mean_g = root->mean_b = 0;
	root->sigma_r = root->sigma_g = root->sigma_b =0;

}


void Quadnode_create(color** r,int width, int height, int pos_x, int pos_y, struct Quadnode* node ,int tolerance){
	int sum_r=0,sum_g=0,sum_b=0;
	int i,j;
	int x = pos_x,y = pos_y;
	node->pos_x = pos_x;
	node->pos_y = pos_y;
	node->width = width;
	node->height = height;
	for(i=x;i<width + x;i++){
		for(j=y;j< height + y;j++){
			sum_r += r[i][j].r;
			sum_b += r[i][j].b;
			sum_g += r[i][j].g;
		}
	}
	node->mean_r = sum_r/height/width;
	node->mean_b = sum_b/height/width;
	node->mean_g = sum_g/height/width;
	int avr_r = node->mean_r;
	int avr_g = node->mean_g;
	int avr_b = node->mean_b;
	for(i=x;i<width + x;i++){
		for(j=y;j<height + y;j++){
			node->sigma_r += (r[i][j].r - avr_r)*(r[i][j].r - avr_r);
			node->sigma_g += (r[i][j].g - avr_g)*(r[i][j].g - avr_g);
			node->sigma_b += (r[i][j].b - avr_b)*(r[i][j].b - avr_b);
		}
	}
	node->sigma_r/=width*height;
	node->sigma_g/=width*height;
	node->sigma_b/=width*height;

	if(node->valid == 1){
		return;
	}

	
	if(node->sigma_r >= tolerance || node->sigma_g >= tolerance || node->sigma_b>= tolerance){
		//对四个子树分别创建四叉树，并赋值
		int width1 = width/2; int height1 = height/2; int posx1 = pos_x; int posy1 = pos_y;
		struct Quadnode * child1 =  (struct Quadnode*)malloc(sizeof(struct Quadnode));
		init_quadnode(child1);
		Quadnode_create(r,width1,height1,posx1,posy1,child1,tolerance);
		node->left_up = child1;


		int width2 = width/2; int height2 = height/2; int posx2 = pos_x + width2; int posy2 = pos_y;
		struct Quadnode * child2 = (struct Quadnode*)malloc(sizeof(struct Quadnode));
		init_quadnode(child2);
		Quadnode_create(r,width2,height2,posx2,posy2,child2,tolerance);
		node->right_up = child2;

		int width3 = width/2; int height3 = height/2; int posx3 = pos_x ; int posy3 = pos_y + height3;
		struct Quadnode * child3 = (struct Quadnode*)malloc(sizeof(struct Quadnode));
		init_quadnode(child3);
		Quadnode_create(r,width3,height3,posx3,posy3,child3,tolerance);
		node->right_up = child3;

		int width4 = width/2; int height4 = height/2; int posx4 = pos_x + width4; int posy4 = pos_y + height4;
		struct Quadnode * child4 = (struct Quadnode*)malloc(sizeof(struct Quadnode));
		init_quadnode(child4);
		Quadnode_create(r,width4,height4,posx4,posy4,child4,tolerance);
		node->right_up = child4;

	}

	
	else{
		node->valid = 1;
		int k,l;
		for(k=node->pos_x;k<node->pos_x + width;k++){
			for(l = node->pos_y;l<node->pos_y + height;l++){
				r[k][l].r = node->mean_r;
				r[k][l].g = node->mean_g;
				r[k][l].b = node->mean_b;
			}
		}
	}


}
