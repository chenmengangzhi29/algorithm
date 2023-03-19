CREATE DATABASE IF NOT EXISTS `RBAC`;
USE `RBAC`;
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account` (
		`id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT '账号ID',
		`user_id` bigint(20) NULL DEFAULT NULL COMMENT '用户ID',
		`open_code` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '登录账号，如手机号等',
		`category` tinyint(1) NULL DEFAULT NULL COMMENT '账号类别',
		`created` datetime(0) NULL DEFAULT NULL COMMENT '创建时间',
		`creator` varchar(36) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '创建人',
		`edited` datetime(0) NULL DEFAULT NULL COMMENT `修改时间`,
		`editor` varchar(36) CHATACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '修改人',
		`deleted` double(1,0) UNSIGNED ZEROFILL NULL DEFAULT 0 COMMENT '逻辑删除:0=未删除，1=已删除',
		PRIMARY KEY (`id`) USING BTREE,
		INDEX `idx_member_id`(`user_id`) USING BTREE COMMENT '普通索引',
		CONSTRAINT `account_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `user` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '账号' ROW_FORMAT = Dynamic;

DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
		`id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT '用户ID',
		`state` tinyint(1) NULL DEFAULT NULL COMMENT '用户状态:0=正常，1=禁用',
		`name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '姓名',
		`head_img_url` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '头像图片地址',
		`mobile` varchar(11) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '手机号码',
		`salt` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '密码加盐',
		`password` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '登录密码',
		`created` datetime(0) NULL DEFAULT NULL COMMENT '创建时间',
		`creator` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '创建人',
		`edited` datetime(0) NULL DEFAULT NULL COMMENT '修改时间',
		`editor` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL DEFAULT NULL COMMENT '修改人',
		`deleted` tinyint(1) UNSIGNED ZEROFILL NULL DEFAULT 0 COMMENT '逻辑删除:0=未删除,1=已删除',
		PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '用户' ROW_FORMAT = Dynamic;

DROP TABLE IF EXISTS `permission`;
CREATE TABLE `permission` (
		`id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT '权限ID',
		`parent_id` bigint(20) NULL DEFAULT NULL COMMENT '所属父级权限ID',
		`code` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '权限唯一CODE代码',
		`name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '权限名称',
		`intro` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '权限介绍',
		`category` tinyint(1) NULL DEFAULT NULL COMMENT '权限类别',
		`uri` bigint(20) NULL DEFAULT NULL COMMENT 'URL规则',
		`created` datetime(0) NULL DEFAULT NULL COMMENT '创建时间',
		`creator` varchar(36) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '创建人',
		`edited` datetime(0) NULL DEFAULT NULL COMMENT '修改时间',
		`editor` varchar(36) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '修改人',
		`deleted` tinyint(1) UNSIGNED ZEROFILL NULL DEFAULT 0 COMMENT '逻辑删除:0=未删除，1=已删除',
		PRIMARY KEY (`id`) USING BTREE,
		INDEX `parent_id`(`parent_id`) USING BTREE COMMENT '父级权限ID',
		INDEX `code`(`code`) USING BTREE COMMENT '权限CODE代码'
)ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '权限' ROW_FORMAT = Dynamic;

DROP TABLE IF EXISTS `role`;
CREATE TABLE `role` (
		`id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT '角色ID',
		`parent_id` bigint(20) NULL DEFAULT NULL COMMENT '所属父级角色ID',
		`code` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '角色唯一CODE代码',
		`name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '角色名称',
		`intro` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '角色介绍',
		`created` datetime(0) NULL DEFAULT NULL COMMENT '创建时间',
		`creator` varchar(36) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '创建人',
		`edited` datetime(0) NULL DEFAULT NULL COMMENT '修改时间',
		`editor` varchar(36) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '修改人',
		`deleted` tinyint(1) UNSIGNED ZEROFILL NULL DEFAULT 0 COMMENT '逻辑删除:0=未删除，1=已删除',
		PRIMARY KEY (`id`) USING BTREE,
		INDEX `parent_id`(`parent_id`) USING BTREE COMMENT '父级权限ID',
		INDEX `code`(`code`) USING BTREE COMMENT '权限CODE代码'
)ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '角色' ROW_FORMAT = Dynamic;

DROP TABLE IF EXISTS `user_role`;
CREATE TABLE `user_role` (
		`id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT 'ID',
		`user_id` bigint(20) NULL DEFAULT NULL COMMENT '用户ID',
		`role_id` bigint(20) NULL DEFAULT NULL COMMENT '角色ID',
		`created` datetime(0) NULL DEFAULT NULL COMMENT '创建时间',
		`creator` varchar(36) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '创建人',
		`edited` datetime(0) NULL DEFAULT NULL COMMENT '修改时间',
		`editor` varchar(36) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '修改人',
		`deleted` tinyint(1) UNSIGNED ZEROFILL NULL DEFAULT 0 COMMENT '逻辑删除:0=未删除，1=已删除',
		PRIMARY KEY (`id`) USING BTREE,
		INDEX `member_id`(`user_id`) USING BTREE COMMENT '用户ID',
		INDEX `role_id`(`role_id`) USING BTREE COMMENT '角色ID'，
		CONSTRAINT `user_role_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `user`(`id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
		CONSTRAINT `user_role_ibfk_2` FOREIGN KEY (`role_id`) REFERENCES `role`(`id`) ON DELETE RESTRICT ON UPDATE RESTRICT
)ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '用户角色' ROW_FORMAT = Dynamic;

DROP TABLE IF EXISTS `role_permission`;
CREATE TABLE `role_permission` (
		`id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT 'ID',
		`role_id` bigint(20) NULL DEFAULT NULL COMMENT '角色ID',
		`permission_id` bigint(20) NULL DEFAULT NULL COMMENT '权限ID',
		`created` datetime(0) NULL DEFAULT NULL COMMENT '创建时间',
		`creator` varchar(36) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '创建人',
		`edited` datetime(0) NULL DEFAULT NULL COMMENT '修改时间',
		`editor` varchar(36) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '修改人',
		`deleted` tinyint(1) UNSIGNED ZEROFILL NULL DEFAULT 0 COMMENT '逻辑删除:0=未删除，1=已删除',
		PRIMARY KEY (`id`) USING BTREE,
		INDEX `role_id`(`role_id`) USING BTREE COMMENT '角色ID',
		INDEX `permission_id`(`permission_id`) USING BTREE COMMENT '权限ID'，
		CONSTRAINT `user_permission_ibfk_1` FOREIGN KEY (`role_id`) REFERENCES `role`(`id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
		CONSTRAINT `user_permission_ibfk_2` FOREIGN KEY (`permission_id`) REFERENCES `permission`(`id`) ON DELETE RESTRICT ON UPDATE RESTRICT
)ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '角色权限' ROW_FORMAT = Dynamic;

DROP TABLE IF EXISTS `user_group`;
CREATE TABLE `user_group` (
		`id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT 'ID',
		`parent_id` bigint(20) NULL DEFAULT NULL COMMENT '所属父级用户组ID',
		`code` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '用户组唯一CODE代码',
		`name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '用户组名称',
		`intro` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '用户组介绍',
		`created` datetime(0) NULL DEFAULT NULL COMMENT '创建时间',
		`creator` varchar(36) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '创建人',
		`edited` datetime(0) NULL DEFAULT NULL COMMENT '修改时间',
		`editor` varchar(36) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '修改人',
		`deleted` tinyint(1) UNSIGNED ZEROFILL NULL DEFAULT 0 COMMENT '逻辑删除:0=未删除，1=已删除',
		PRIMARY KEY (`id`) USING BTREE,
		INDEX `parent_id`(`parent_id`) USING BTREE COMMENT '父级用户组ID',
		INDEX `code`(`code`) USING BTREE COMMENT '用户组CODE代码'
)ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '用户组' ROW_FORMAT = Dynamic;

DROP TABLE IF EXISTS `user_group_user`;
CREATE TABLE `user_group_user` (
		`id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT 'ID',
		`user_group_id` bigint(20) NULL DEFAULT NULL COMMENT '用户组ID',
		`user_id` bigint(20) NULL DEFAULT NULL COMMENT '用户ID',
		`created` datetime(0) NULL DEFAULT NULL COMMENT '创建时间',
		`creator` varchar(36) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '创建人',
		`edited` datetime(0) NULL DEFAULT NULL COMMENT '修改时间',
		`editor` varchar(36) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '修改人',
		`deleted` tinyint(1) UNSIGNED ZEROFILL NULL DEFAULT 0 COMMENT '逻辑删除:0=未删除，1=已删除',
		PRIMARY KEY (`id`) USING BTREE,
		INDEX `member_group_id`(`user_group_id`) USING BTREE COMMENT '用户组ID',
		INDEX `member_id`(`user_id`) USING BTREE COMMENT '用户ID'，
		CONSTRAINT `user_group_user_ibfk_1` FOREIGN KEY (`user_group_id`) REFERENCES `user_group`(`id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
		CONSTRAINT `user_group_user_ibfk_2` FOREIGN KEY (`user_id`) REFERENCES `user`(`id`) ON DELETE RESTRICT ON UPDATE RESTRICT
)ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '用户组成员' ROW_FORMAT = Dynamic;

DROP TABLE IF EXISTS `user_group_role`;
CREATE TABLE `user_group_role` (
		`id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT 'ID',
		`user_group_id` bigint(20) NULL DEFAULT NULL COMMENT '用户组ID',
		`role_id` bigint(20) NULL DEFAULT NULL COMMENT '角色ID',
		`created` datetime(0) NULL DEFAULT NULL COMMENT '创建时间',
		`creator` varchar(36) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '创建人',
		`edited` datetime(0) NULL DEFAULT NULL COMMENT '修改时间',
		`editor` varchar(36) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '修改人',
		`deleted` tinyint(1) UNSIGNED ZEROFILL NULL DEFAULT 0 COMMENT '逻辑删除:0=未删除，1=已删除',
		PRIMARY KEY (`id`) USING BTREE,
		INDEX `member_group_id`(`user_group_id`) USING BTREE COMMENT '用户组ID',
		INDEX `role_id`(`role_id`) USING BTREE COMMENT '角色ID'，
		CONSTRAINT `user_group_role_ibfk_1` FOREIGN KEY (`user_group_id`) REFERENCES `user_group`(`id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
		CONSTRAINT `user_group_role_ibfk_2` FOREIGN KEY (`role_id`) REFERENCES `role`(`id`) ON DELETE RESTRICT ON UPDATE RESTRICT
)ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '用户组角色' ROW_FORMAT = Dynamic;











