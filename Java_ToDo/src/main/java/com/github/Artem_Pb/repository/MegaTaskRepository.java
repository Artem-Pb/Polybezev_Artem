package com.github.Artem_Pb.repository;

import com.github.Artem_Pb.domain.MegaTask;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import java.util.List;

public interface MegaTaskRepository extends JpaRepository<MegaTask, Long> {
    @Query("select distinct m from MegaTask m " +
            "left join m.subTasks s " +
            "where lower(m.title) like lower(concat('%', :keyword, '%')) " +
            "or lower(s.title) like lower(concat('%', :keyword, '%'))")
    List<MegaTask> findByTitleOrSubTaskTitleContaining(@Param("keyword") String keyword);
}
