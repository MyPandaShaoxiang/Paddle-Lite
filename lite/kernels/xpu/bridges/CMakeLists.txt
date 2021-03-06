lite_cc_library(xpu_bridge_registry SRCS registry.cc)

set(xpu_bridge_deps xpu_bridge_registry xpu_builder op)

lite_cc_library(xpu_bridge_act_op SRCS act_op.cc DEPS ${xpu_bridge_deps})
lite_cc_library(xpu_bridge_conv_op SRCS conv_op.cc DEPS ${xpu_bridge_deps})
lite_cc_library(xpu_bridge_elementwise_ops SRCS elementwise_ops.cc DEPS ${xpu_bridge_deps})
lite_cc_library(xpu_bridge_pool_op SRCS pool_op.cc DEPS ${xpu_bridge_deps})
lite_cc_library(xpu_bridge_softmax_op SRCS softmax_op.cc DEPS ${xpu_bridge_deps})
lite_cc_library(xpu_bridge_mul_op SRCS mul_op.cc DEPS ${xpu_bridge_deps})

set(xpu_bridges
        xpu_bridge_registry
        xpu_bridge_act_op
        xpu_bridge_conv_op
        xpu_bridge_elementwise_ops
        xpu_bridge_pool_op
        xpu_bridge_softmax_op
        xpu_bridge_mul_op
        CACHE INTERNAL "xpu_bridges")

set(xpu_bridge_test_deps ${xpu_bridges} ${xpu_kernels} ${ops})

lite_cc_test(test_xpu_bridge_act_op SRCS act_op_test.cc test_helper.cc DEPS ${xpu_bridge_test_deps})
lite_cc_test(test_xpu_bridge_conv_op SRCS conv_op_test.cc test_helper.cc DEPS ${xpu_bridge_test_deps})
lite_cc_test(test_xpu_bridge_elementwise_ops SRCS elementwise_ops_test.cc test_helper.cc DEPS ${xpu_bridge_test_deps})
lite_cc_test(test_xpu_bridge_pool_op SRCS pool_op_test.cc test_helper.cc DEPS ${xpu_bridge_test_deps})
lite_cc_test(test_xpu_bridge_softmax_op SRCS softmax_op_test.cc test_helper.cc DEPS ${xpu_bridge_test_deps})
lite_cc_test(test_xpu_bridge_mul_op SRCS mul_op_test.cc test_helper.cc DEPS ${xpu_bridge_test_deps})
