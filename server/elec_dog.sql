-- 创建数据库
create DATABASE elec_dog;


-- 创建用户基本信息表

CREATE TABLE `user_info`
(
	id 			int 		NOT NULL AUTO_INCREMENT,		-- index
	user_id	int(10)	NOT NULL COMMENT '用户id',
	real_name VARCHAR(20)	COMMENT '真实姓名',
	address VARCHAR(256)	COMMENT	'地址',
	pwd 	VARCHAR(128) NOT NULL COMMENT '密码',
	phone int(11)	COMMENT '手机号',
	email VARCHAR(128)	NOT NULL COMMENT '邮箱',
	icon VARCHAR(256)	NOT NULL COMMENT	'头像url',
	register_time int(11)	NOT NULL COMMENT '注册时间戳',
	last_login int(11)	COMMENT	'上次登录时间戳',
	PRIMARY KEY (id)
) ENGINE = InnoDB;



-- 好友关系表

CREATE TABLE `relation_friend` (
  `index` int(10) NOT NULL AUTO_INCREMENT COMMENT '序号',
  `my_id` int(11) NOT NULL COMMENT '用户id',
  `friend_id` int(11) NOT NULL COMMENT '好友id',
  `add_time` int(11) DEFAULT NULL COMMENT '添加时间',
  PRIMARY KEY (`index`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;